#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <cassert>

using namespace std;

#ifndef BUFSIZ
#define BUFSIZ 1024
#endif

int StoI(string s)
{
    int R;
    R = (s[0] - '0')*100;
    R += (s[1]- '0')*10;
    R += (s[2]- '0');
    return R;
}


string ItoS(int I)
{
    string R = "000";
    R[2] = I % 10 + '0';
    I /= 10;
    R[1] = I % 10 + '0';
    I /= 10;
    R[0] = I % 10 + '0';

    return R;
}

int main() {
    std::ios::sync_with_stdio(false);
    int n, runCommand;
	char lineBuffer[BUFSIZ];

    cin >> n;
	cin.getline(lineBuffer, BUFSIZ);
	cin.getline(lineBuffer, BUFSIZ);

    bool halt = false;
    string instructions[1000] ;
    int pc = 0;


	while(n--) {
        for (int i = 0; i < 1000; i++) instructions[i] = "000";

        // int RAM[1000];
        int instIdx = 0;

        while(cin.getline(lineBuffer, BUFSIZ) && cin.gcount() > 1) {
			stringstream stream(lineBuffer);
			stream >> instructions[instIdx++];
            // RAM[instIdx - 1] = std::stoi(instructions[instIdx - 1]);
		}

        int reg[10];
        for (int i = 0; i < 10; i++) reg[i] = 0;
        runCommand = 0;
        halt = false;
        pc = 0;
        // int cmd[3], d,s,a;

        while (!halt) {
        // for (int pc = 0; pc < instIdx && !halt; pc++) {
            runCommand++;
            // cout << "RAM[" << pc << "] :" << instructions[pc] << " ==> ";

            int op1 = int(instructions[pc][1] - '0');
            int op2 = int(instructions[pc][2] - '0');

            switch (instructions[pc][0]) {
                case '1':
                    halt = true;
                    pc++;
                    break;
                case '2':
                    reg[op1] = op2;
                    pc++;
                    break;
                case '3':
                    reg[op1] = (reg[op1] + op2) % 1000;
                    pc++;
                    break;
                case '4':
                    reg[op1] = (reg[op1] * op2) % 1000;
                    pc++;
                    break;
                case '5':
                    reg[op1] = reg[op2];
                    pc++;
                    break;
                case '6':
                    reg[op1] = (reg[op1] + reg[op2]) % 1000;
                    pc++;
                    break;
                case '7':
                    reg[op1] = (reg[op1] * reg[op2]) % 1000;
                    pc++;
                    break;
                case '8':
                    reg[op1] = std::stoi(instructions[reg[op2]]);
                    pc++;
                    break;
                case '9':
                    instructions[reg[op2]] = ItoS(reg[op1]);
                    pc++;
                    break;
                case '0':
                    if (reg[op2] != 0)
                        pc = reg[op1];
                    else
                        pc++;
                    break;
            }

            // cout << op1 << " , " << op2 << " ||| [";
            // cout << "]" << endl;
        }
        cout << runCommand << endl;
		if(n != 0) cout << endl;
	}

	return 0;
}
