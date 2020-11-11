/*
 * FILE: uva-tool.cpp
 *
 * @author: Arafat Hasan Jenin <arafathasanjenin[at]gmail[dot]com>
 *
 * LINK: https://github.com/AHJenin/uva-tool
 *
 * DATE CREATED: 29 Feb 2017
 * LAST MODIFIED: 29-10-17 20:10:58 (+06)
 *
 * DESCRIPTION:
 *
 * DEVELOPMENT HISTORY:
 * Date         Version     Description
 * --------------------------------------------------------------------
 *  29 Feb 2017 0.2         Completed, not tested, BASH
 *  02 Apr 2017 0.4         Without bash script, fully C++, system() used
 *  05 Oct 2017 0.6         Cleanize, nlohmann/json used
 *
 *               _/  _/_/_/_/  _/      _/  _/_/_/  _/      _/
 *              _/  _/        _/_/    _/    _/    _/_/    _/
 *             _/  _/_/_/    _/  _/  _/    _/    _/  _/  _/
 *      _/    _/  _/        _/    _/_/    _/    _/    _/_/
 *       _/_/    _/_/_/_/  _/      _/  _/_/_/  _/      _/
 */

///////////////////////////////////////////////////////////////////////

#include <iostream> // std IO
#include <fstream> // std::ifstream
#include "include/json.hpp" // json praser
#include <unistd.h> // getlogin()

using namespace std;
using json = nlohmann::json;

#ifdef __linux__
    const string szHome = getlogin(); // szHome is loginusername in the system
    const string pid_num_cvs = "/usr/share/uva-tool/pid-to-num.cvs";
    const string cookie_file =
    "/home/" + szHome + "/.cache/uva-tool/uva.onlinejudge.org_cookie.txt";
    //const string err = " 2> ~/.uva-tool/err.log";
    const string err = " 2> /dev/null";
    const string curlfunc = "curl";
#elif __WIN32__
    // win
#endif



string system_exec (const char *cmd) {
    char buffer[128];
    string result = "";
    FILE *pipe = popen (cmd, "r");

    if (!pipe) throw runtime_error ("popen() failed!");

    try {
        while (!feof (pipe) ) {
            if (fgets (buffer, 128, pipe) != NULL)
                result += buffer;
        }

    } catch (...) {
        pclose (pipe);
        throw;
    }

    pclose (pipe);
    return result;
}

class Problem {
    private:
        string line, pname;
        int pid, pnum;
        map<int, pair<int, string> > pid_name;
        void split (string splitit) {
            istringstream ss (splitit);
            vector<string> result;
            string token;

            while (getline (ss, token, '~') ) {
                result.push_back (token);
            }

            pid = stoi (result[0]);
            pnum = stoi (result[1]);
            pname = result[2];
        }

    public:
        Problem() {
            ifstream fp (pid_num_cvs);

            if (!fp) {
                cerr << "Unable to open file : " << pid_num_cvs << "\n";
                throw 1;
            }

            while (getline (fp, line) ) {
                split (line);
                pid_name[pid] = make_pair (pnum, pname);
            }

            fp.close();
        }
        string name (int pidd) {
            return pid_name[pidd].second;
        }

        int number (int pidd) {
            return pid_name[pidd].first;
        }
};


class Submission {

    private:
        int range;
        json json_subs;
        Problem *problem;
        void convertunixtime (long long u) {
            time_t     now;
            struct tm *ts;
            char       buf[80];
            now = u;
            /* Format and print the time, "ddd yyyy-mm-dd hh:mm:ss zzz" */
            ts = localtime (&now);
            strftime (buf, sizeof (buf), "%d-%m-%y %I:%M:%S%p %Z", ts);
            cout << buf;
        }

        void sid (long long sub_id) {
            cout << left << setw (11) << sub_id;
        }

        void problem_name (int pid) {
            cout << problem->number (pid) << '-' \
                 << left << setw (36) << problem->name (pid) << '\t';
        }

        void verdict (int ver) {
            if (ver == 90)
                cout << "\x1b[38;2;0;195;0m\033[1mAccepted\033[0m\x1b[0m\t";
            else if (ver == 80)
                cout << "\x1b[38;2;102;102;0m\033[1mPresentationE\033[0m\x1b[0m\t";
            else if (ver == 70)
                cout << "\x1b[38;2;255;0;0m\033[1mWrong answer\033[0m\x1b[0m\t";
            else if (ver == 60)
                cout << "\x1b[38;2;51;51;255m\033[1mMemory limit\033[0m\x1b[0m\t";
            else if (ver == 50)
                cout << "\x1b[38;2;0;0;255m\033[1mTime limit\033[0m\x1b[0m\t";
            else if (ver == 45)
                cout << "\x1b[38;2;96;96;96m\033[1mOutput limit\033[0m\x1b[0m\t";
            else if (ver == 40)
                cout << "\x1b[38;2;0;204;204m\033[1mRuntime error\033[0m\x1b[0m\t";
            else if (ver == 30)
                cout << "\x1b[38;2;204;204;0m\033[1mCompile error\033[0m\x1b[0m\t";
            else if (ver == 35)
                cout << "\x1b[38;2;96;96;96m\033[1mRestricted function\033[0m\x1b[0m\t";
            else if (ver == 20 || ver == 0)
                cout << "\x1b[38;2;96;96;96m\033[1mIn queue\033[0m\x1b[0m\t";
            else if (ver == 15)
                cout << "\x1b[38;2;96;96;96m\033[1mCan't be judged\033[0m\x1b[0\t";
            else if (ver == 10)
                cout << "\x1b[38;2;96;96;96m\033[1mSubmission error\033[0m\x1b[0m ";
            else  cout << "UNKNOWN VERDICT\t";
        }

        void runtime (int rt, int ver) {
            double runt = (double) (rt) / 1000.0;

            if (ver == 40 || ver == 45 || ver == 50 || ver == 60 || ver == 70 || \
                ver == 80 || ver == 90 )
                cout << left << setw (6) << fixed << setprecision (3) << runt << "\t";
            else cout << left << setw (8) << "-";
        }

        void uva_rank (int rnk) {
            if (rnk != -1) cout << left << setw (6) << rnk << "\t";
            else cout << left << setw (8) << "-";
        }

        void language (int lan) {
            if (lan == 6) cout << "Python" << "\t";
            else if (lan == 5) cout << "C++11" << "\t";
            else if (lan == 4) cout << "Pascal" << "\t";
            else if (lan == 3) cout << "C++" << "\t";
            else if (lan == 2) cout << "Java" << "\t";
            else if (lan == 1) cout << "ANSI C" << "\t";
            else cout << "UNKNOWN" << "\t";

            cout << "   ";
        }
        void date (long long utime) {
            convertunixtime (utime);
            cout << '\t';
            cout << "\n";
        }

    public:
        Submission (string &input) {
            try {
                json_subs = json::parse (input);

            } catch (json::parse_error &e) {
                std::cerr << e.what() << std::endl;
                throw 2;
            }

            range = (int) json_subs["subs"].size();
        }

        void show (Problem &input) {
            problem = &input;
            cout << left << setw (11) << "Sub ID" << setw (40) << "Problem\t" << \
                 "Verdict\t\t" << "Runtime\t" << "Rank\t" << "Language   " << \
                 "Date\n";
            cout << "=============================================================";
            cout << "=============================================================\n";

            for (int i = range - 1; i >= 0; i--) {
                sid (json_subs["subs"][i][0]);
                problem_name (json_subs["subs"][i][1]);
                verdict ( (json_subs["subs"][i][2]) );
                runtime (json_subs["subs"][i][3], json_subs["subs"][i][2]);
                uva_rank (json_subs["subs"][i][6]);
                language (json_subs["subs"][i][5]);
                date (json_subs["subs"][i][4]);
            }
        }
};


void hunt (string name, string range) {
    string cmd, uid, subs_usr_last, tmp;
    Problem problem;
    cmd = curlfunc + " http://uhunt.onlinejudge.org/api/uname2uid/" + \
          name + err;
    uid = system_exec (cmd.c_str() );

    if (uid == "") {
        cerr << "Unable to connect or curl executing error\n";
        throw 3;
    }

    cmd.clear();
    cmd = curlfunc + " http://uhunt.onlinejudge.org/api/subs-user-last/" + \
          uid + "/" + range + err;
    subs_usr_last = system_exec (cmd.c_str() );
    Submission usr_last_subs (subs_usr_last);
    usr_last_subs.show (problem);
}

class submit {
    private:
        string cookie_jar = cookie_file;
        string submitlink = "https://onlinejudge.org/index.php\
?option=com_onlinejudge&Itemid=25&page=save_submission";
        string formdata() {
            string cmd = curlfunc + " -f -L -s http://onlinejudge.org |";
            cmd += " grep -B8 'id=\"mod_login_remember\"' | awk '{print $3 \" \" $4}'";
            string str = system_exec (cmd.c_str() );

            if (str == "") return str;

            size_t start = str.find ("name=\"");

            while (start != string::npos) {
                str.erase (start, 6);
                start = str.find ("name=\"");
            }

            start = str.find ("\" value=\"");

            while (start != string::npos) {
                str.replace (start, 9, "=");
                start = str.find ("\" value=\"");
            }

            start = str.find ("\"");

            while (start != string::npos) {
                str.erase (start, 1);
                start = str.find ("\"");
            }

            str.erase (str.find ("remember id=mod_login_remember"), 30);
            start = str.find ("\n");

            while (start != string::npos) {
                str.replace (start, 1, "&");
                start = str.find ("\n");
            }

            str.erase (str.find ("&&"), 2);
            string usr, pass, remember;
            cout << "Input username: ";
            cin >> usr;
            cout << "Input password: ";
            cin >> pass;
            cout << "Remember? [y/n] ";
            cin >> remember;
            remember = (remember == "y" or remember == "Y" ? "yes" : "no");
            string usrpass = "username=" + usr + "&passwd=" + pass + \
                             "&remember=" + remember + "&";
            return usrpass + str;
        }

    public:
        bool logout() {
            string cmd = "rm " + cookie_jar + " 2>&1";
            string str = system_exec (cmd.c_str() );

            if (str == "") return true;

            return false;
        }

        bool login() {
            string data = formdata();

            if (data == "") {
                cout << "Can not connect to onlinejudge.org\n";
                return false;
            }

            string cmd = curlfunc + " -X POST -f -L -s --compressed ";
            cmd += "--cookie-jar " + cookie_jar + " --data \"";
            cmd += data;
            cmd += "\" \"https://onlinejudge.org/index.php\
?option=com_comprofiler&task=login\"";
            string str = system_exec (cmd.c_str() );

            if (str.find ("My Account") != string::npos
                and str.find ("Logout") != string::npos) {
                return true;
            }

            return false;
        }

        void problem_submit (string pnumber, string ppath, string plang) {
            string cmd = curlfunc + \
                         " -X POST -f -L -s -w '%{url_effective}' " \
                         "--compressed --cookie " \
                         + cookie_jar + " --cookie-jar " + cookie_jar + \
                         " --form localid=" + pnumber + " --form language=" + plang + \
                         " --form \"codeupl=@" + ppath + "\" \"" + submitlink + "\"";
            string str = system_exec (cmd.c_str() );
            size_t notlogin = str.find ("You are not authorised to view this resource");
            size_t subid = str.find ("mosmsg=Submission+received+with+ID+");

            if (str == submitlink)
                cout << "Can not connect to onlinejudge.org\n";
            else if (notlogin != string::npos) {
                cout << "Not logged in\n";

            } else if (subid != string::npos) {
                size_t sz = str.find ("\"", subid);
                cout << "Submission received with ID ";

                for (size_t i = subid + 35; i < sz; i++)
                    cout << str[i];

                cout << '\n';
            }
        }
};

int main (int argc, char *argv[]) {
    try {
        if (argc == 6 && !strcmp (argv[1], "-hunt") && !strcmp (argv[2], "-u")
            && !strcmp (argv[4], "-r") ) {
            hunt (argv[3], argv[5]);

        } else if (argc == 5 && !strcmp (argv[1], "-submit") ) {
            submit sub;
            sub.problem_submit (argv[2], argv[3], argv[4]);

        } else if (argc == 2 && !strcmp (argv[1], "-login") ) {
            submit sub;

            if (sub.login() ) {
                cout << "Logged in\n";

            } else cout << "Log in failed\n";

        } else if (argc == 2 && !strcmp (argv[1], "-logout") ) {
            submit sub;

            if (sub.logout() ) {
                cout << "Logged out\n";

            } else cout << "Not logged in\n";

        } else cout << "Wrong option\n";

    } catch (int exception) {
        cerr << "Exeption no: " << exception << '\n';
    }

    return 0;
}

