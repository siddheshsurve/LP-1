#include <bits/stdc++.h> 
typedef long long int ll; 
using namespace std; 
void NTP(string h, string m) 
{ 
    int hrs = stoi(h); 
    int mins = stoi(m); 
    cout << "The original time at UTC server is: " << hrs << " : " << mins << endl; 
    int t1, t2, t3, t4; 
    cout << "Enter value of t1: "; 
    cin >> t1; 
    cout << "Enter value of t2: "; 
    cin >> t2; 
    cout << "Enter value of t3: "; 
    cin >> t3; 
    cout << "Enter value of t4: "; 
    cin >> t4; 
    float delay = 9999, offset = 9999; 
    for (float i = -0.3; i < 0.4; i += 0.1) 
    { 
        float del = (float)(((t4 + i) - (t1 + i)) - ((t3 + i) - (t2 + i))) / (float)2; 
        float offs = (float)(((t2 + i) - (t1 + i)) + ((t3 + i) - (t4 + i))) / (float)2; 
        if (abs((int)del) < delay) 
        { 
            delay = abs((int)del); 
            offset = offs; 
        } 
    } 
    cout << "\nThe delay for secondary server is: " << delay << endl; 
    cout << "The offset for secondary server is: " << (int)offset << endl; 
    mins += offset; 
    while (mins >= 60) 
    { 
        hrs += 1; 
        mins -= 60; 
    } 
    cout << "\nHence, after adding offset, time at secondary server: " << hrs << " : " << mins << endl; 
} 

void display(int e1, int e2, int p1[5], int p2[3]) 
{ 
    int i; 
    cout << "\nThe time stamps of events in P1:\n"; 
    for (i = 0; i < e1; i++) 
    { 
        cout << p1[i] << " "; 
    } 
    cout << "\nThe time stamps of events in P2:\n"; 
    for (i = 0; i < e2; i++) 
    cout << p2[i] << " "; 
    cout << endl; 
} 
void lamportLogicalClock(int e1, int e2, int m[5][3]) 
{ 
    int i, j, k, p1[e1], p2[e2]; 
    for (i = 0; i < e1; i++) 
        p1[i] = i + 1; 
    for (i = 0; i < e2; i++) 
        p2[i] = i + 1; 
    cout << "Schedule of events and messages is: " << endl; 
    cout << "\t"; 
    for (i = 0; i < e2; i++) 
        cout << "\te2" << i + 1; 
    for (i = 0; i < e1; i++) 
    { 
        cout << "\n e1" << i + 1 << "\t"; 
        for (j = 0; j < e2; j++) 
        cout << m[i][j] << "\t"; 
    } 
    for (i = 0; i < e1; i++) 
    { 
        for (j = 0; j < e2; j++) 
        { 
            if (m[i][j] == 1) 
            { 
                p2[j] = max(p2[j], p1[i] + 1); 
                for (k = j + 1; k < e2; k++) 
                p2[k] = p2[k - 1] + 1; 
            } 
            if (m[i][j] == -1) 
            { 
                p1[i] = max(p1[i], p2[j] + 1); 
                for (k = i + 1; k < e1; k++) 
                p1[k] = p1[k - 1] + 1; 
            } 
        } 
    } 
    display(e1, e2, p1, p2); 
} 
    
int main() 
{ 
    int cho; 
    string ss, a, b;
    while (true) 
    { 
        cout << "\n1.Lamport's Clock\n2.NTP\nEnter simulation to check: "; 
        cin >> cho; 
        int e1 = 5, e2 = 3, m[5][3]; 
        // m[0][0] = 0; 
        // m[0][1] = 0; 
        // m[0][2] = 0; 
        // m[1][0] = 0; 
        // m[1][1] = 0; 
        // m[1][2] = 1; 
        // m[2][0] = 0; 
        // m[2][1] = 0; 
        // m[2][2] = 0; 
        // m[3][0] = 0; 
        // m[3][1] = 0; 
        // m[3][2] = 0; 
        // m[4][0] = 0; 
        // m[4][1] = -1; 
        // m[4][2] = 0;
        for(int i=0; i<5; i++) {
            for(int j=0; j<3; j++) {
                cout<<"m["<<i<<"]["<<j<<"] = "; 
                cin>>m[i][j];
            }
        }
        if (cho == 1) 
            lamportLogicalClock(e1, e2, m);
        if (cho == 2) 
        { 
            cout << "Enter UTC time in HH:MM format: "; 
            cin >> ss; 
            int i = 0; 
            while (ss[i] != ':') 
            { 
                a += ss[i]; 
                i++; 
            } 
            i++; 
            while (ss[i]) 
            { 
                b += ss[i]; 
                i++; 
            } 
            NTP(a, b);
            break;
        } 
    } 
    return 0; 
}