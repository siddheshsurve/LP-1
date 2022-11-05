#include <bits/stdc++.h>
#include <fstream>
using namespace std;

void spltline(string s, vector<string> &v)
{

    string temp = "";

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ' ' || s[i] == ',')
        {
            if (temp != "" && temp != " ")
                v.push_back(temp);
            temp = "";
        }
        else
        {
            temp = temp + s[i];
        }
    }
    if (temp != "" && temp != " ")
    {
        v.push_back(temp);
    }
}

// search in vector
int search_vector(vector<string> v, string k)
{
    auto it = find(v.begin(), v.end(), k);
    if (it != v.end())
    {
        int index = it - v.begin();
        return index;
    }
    else
    {
        return -1;
    }
}

int main()
{
    fstream ff, f;
    ff.open("program.txt", ios::in | ios::out);
    f.open("out.txt", ios::in | ios::out);
    string line;
    // vector to store macro name
    vector<string> mnt;
    // vector to store index of mdt for macro in mnt;
    vector<int> mdt_index;
    // vector to store arguments
    vector<string> ala;
    // vector to store mdt
    vector<string> mdt;
    // vector to know from where the arguments are stored in ala for particular macro
    vector<int> arg_start;

    bool macenc = false; // to keep track of macroname and arguments line
    bool mac = false;    // to know wheather we are in macro or not
    while (ff)
    {
        if (ff.eof())
        {
            break;
        }
        getline(ff, line);
        if (line == "")
        {
            continue;
        }

        vector<string> v;
        spltline(line, v);
        // cout<<"v[0] is: "<<v[0]<<endl;
        if (v[0] == "MACRO")
        {
            macenc = true;
            mac = true;
            continue;
        }
        else if (!mac)
        {
            f << line << endl;
        }
        else if (v[0] == "MEND")
        {
            mac = false;
        }
        else if (macenc)
        {
            macenc = false;
            mnt.push_back(v[0]);
            arg_start.push_back(ala.size());
            for (int i = 1; i < v.size(); i++)
            {
                ala.push_back(v[i]);
            }
            mdt_index.push_back(mdt.size());
            mdt.push_back(line);
        }

        if (mac)
        {
            string mdt_line = "";
            for (int i = 0; i < v.size(); i++)
            {
                if (search_vector(ala, v[i]) == -1)
                {
                    mdt_line += v[i] + " ";
                }
                else
                {
                    mdt_line += to_string(search_vector(ala, v[i])) + " ";
                }
            }
            mdt.push_back(mdt_line);
        }

        if (ff.eof())
        {
            break;
        }
    }
    ff.close();
    mdt_index.push_back(mdt.size());
    arg_start.push_back(ala.size());
    cout << "MNT is: \n";
    for (int i = 0; i < mnt.size(); i++)
    {
        cout << mnt[i] << endl;
    }
    cout << endl;
    cout << "ala is: \n";
    for (int i = 0; i < ala.size(); i++)
    {
        cout << ala[i] << endl;
    }
    cout << endl;
    cout << "mdt is: \n";
    for (int i = 0; i < mdt.size(); i++)
    {
        cout << mdt[i] << endl;
    }
    cout << endl;
    cout << "mdt_index is: \n";
    for (int i = 0; i < mdt_index.size(); i++)
    {
        cout << mdt_index[i] << endl;
    }
    cout << endl;
    cout << "arg_start is: \n";
    for (int i = 0; i < arg_start.size(); i++)
    {
        cout << arg_start[i] << endl;
    }
    cout << endl;
    f.close();
    // pass 2 of macro processor
    f.open("out.txt", ios::in | ios::out);
    fstream fff;
    fff.open("out2.txt", ios::in | ios::out);
    while (f)
    {
        if (f.eof())
        {
            break;
        }
        getline(f, line);
        if (line == "")
        {
            continue;
        }
        vector<string> v;
        spltline(line, v);
        if (search_vector(mnt, v[0]) != -1)
        {
            int ind = search_vector(mnt, v[0]);
            int arg_ind_from = arg_start[ind];
            int arg_ind_end = arg_start[ind + 1] - 1;
            int mdt_ind_from = mdt_index[ind] + 2;
            int mdt_ind_end = mdt_index[ind + 1] - 1;
            vector<string> temp_v;
            for (int i = 1; i < v.size(); i++)
            {
                temp_v.push_back(v[i]);
            }
            for (int i = mdt_ind_from; i <= mdt_ind_end; i++)
            {
                // perform manipulation for each line of mdt here and you are done!!!
                string curr_line = mdt[i];
                vector<string> each_word;
                spltline(curr_line, each_word);
                string output2 = "";
                for (int m = 0; m < each_word.size(); m++)
                {
                    if (isdigit(each_word[m][0]))
                    {
                        int argnum = stoi(each_word[m]);
                        output2 += temp_v[argnum - arg_ind_from] + " ";
                    }
                    else
                    {
                        output2 += each_word[m] + " ";
                    }
                }
                fff << output2 << endl;
            }
        }
        else
        {
            fff << line << endl;
        }
        if (f.eof())
        {
            break;
        }
    }
    ff.close();
    f.close();
    fff.close();
}