#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class GuessIt
{
    private:

    struct node
    {
        string data1,data2;
        node *left,*right;
    };

    node *root,*broot,*proot;
    char YorN;
    string track,answer,newQuestion,oldAnswer,s;
    bool GameOver;
    char enter;
    int count;

    public:

    GuessIt()
    {
        root=NULL;
        broot=NULL;
        proot=NULL;
        track=("");
        GameOver=false;
        count=0;
    }
    void instructions()
    {
        system("Color B0");

        for(int i=0;i<12;i++)cout << endl;

        cout << setw(87) << "Hello and welcome to the animal guessing game " << (char)1 << endl << endl;
        cout << setw(111) << "Here is how it works, you will think of an animal, and the computer is going to try to guess it." << endl << endl;
        cout << setw(103) << "You might be thinking that the computer might not be able to guess the animal that " << endl << endl;
        cout << setw(101) << "you have thought of, which could be correct but heres where it gets interesting," << endl << endl;
        cout << setw(95) << "every time the computer gets a guess wrong, it's knowledge is updated" << endl << endl;
        cout << setw(103) << "as revealing the animal that you have thought of, gets stored in the computer's memory." << endl << endl;
        cout << setw(99) << "This in turn ensures that the computer does not make the same mistake again." << endl << endl;
        cout << setw(107) << "Interesting right? Well what are you waiting for? Press ENTER and let the fun times begin " << (char)1 << endl << endl;

        while(1)
        {
            if(kbhit())
            {
                enter=getch();
                if(enter==13)
                {
                    break;
                }
            }
        }
    }

    void SetQuestionsTree()
    {

        root=NULL;
        ifstream infile;
        string question;
        infile.open("20Q.txt");

        if(!infile)
        {
            cerr << "Sorry, this file does not exist " << (char)2 << endl;
            exit(0);
        }

        while(getline(infile,question))
        {
            if(root==NULL)
            {
                root=CreateLeaf(question);
                proot=root;
            }
            else
            {
                while(question[count]=='R' || question[count]=='L')
                {
                    if(question[count]=='R')
                    {
                        if(proot->right==NULL)
                        {
                            proot->right=CreateLeaf(question);
                        }
                        else
                        {
                            proot=proot->right;
                        }
                    }
                    else if(question[count]=='L')
                    {
                        if(proot->left==NULL)
                        {
                            proot->left=CreateLeaf(question);
                        }
                        else
                        {
                            proot=proot->left;
                        }
                    }
                    count++;
                }
                count=0;
                proot=root;
            }
        }

        infile.close();
    }

    node* CreateLeaf(string q)
    {
        string newq;
        node *leaf=new node;
        for(int i=0;i<q.size();i++)
        {
            if(q[i]==' ')
            {
                for(int j=i+1;j<q.size();j++)
                {
                    newq+=q[j];
                }
                break;
            }
        }
        leaf->left=NULL;
        leaf->right=NULL;
        leaf->data1=newq;
        leaf->data2=q;
        return leaf;
    }

    void GameOn()
    {
        GameOver=false;
        broot=root;
        track=("");
        do
        {
            system("Color F5");
            cout << setw(72) << broot->data1 << "(y/n)";
            cin >> YorN;
            cin.ignore();

            if(broot->left==NULL && broot->right==NULL && YorN=='y')
            {
                for(int i=0;i<5;i++)
                {
                    system("CLS");
                    system("Color 5F");
                    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
                    Sleep(600);
                    cout << setw(87) << "Yesssss!!! I win! Thank you so much for playing " << (char)1 << endl << endl;
                        Sleep(600);
                }
                GameOver=true;
            }
            else if(broot->left==NULL && broot->right==NULL && YorN=='n')
            {
                system("CLS");
                GimmeKnowledge();
                GameOver=true;
            }
            else if(YorN=='y')
            {
                broot=broot->left;
                track+="L";
            }
            else if(YorN=='n')
            {
                broot=broot->right;
                track+="R";
            }
        }while(GameOver==false);
    }

    void GimmeKnowledge()
    {

        system("Color 20");
        for(int i=0;i<20;i++)cout << endl;
        cout << setw(81) << "Okay, I give up, tell me what it is? " << (char)2;
        getline(cin,answer);

        system("CLS");

        for(int i=broot->data1.size()-2;i>=0;i--)
        {
            if(broot->data1[i]==' ')break;
            else s+=broot->data1[i];
            }

        for(int i=s.size()-1;i>=0;i--)oldAnswer+=s[i];


        for(int i=0;i<15;i++)cout << endl;

        cout << endl << endl << setw(83) << "Please enter a question for which the answer is NO for '" << oldAnswer << "'";
            cout << endl << setw(62) << "and YES for '" << answer << "'.";

            getline(cin,newQuestion);

            string line;
            ifstream in;
            ifstream in2;
            ofstream out;
            ofstream out2;

            in.open("20Q.txt");
            out.open("20Q2.txt");

            if(!in || !out)
            {
                cerr << "Sorry, the file does not exist " << (char)2 << endl << endl;
                exit(0);
            }

            while(getline(in,line))
            {
                if(line==broot->data2)
                {
                    newQuestion=track+" "+newQuestion;
                    out << newQuestion << endl;
                }
                else
                {
                    out << line << endl;
                }
            }

            in.clear();
            in.seekg(0,ios::beg);
            in2.open("20Q2.txt");
            out2.open("20Q.txt");

            if(!in2 || !out2)
            {
                cerr << "Sorry, the file does not exist " << (char)2 << endl << endl;
                exit(0);
            }

            while(getline(in2,line))
            {
                out2 << line << endl;
            }

            if(answer[0]=='A' || answer[0]=='E' || answer[0]=='I' || answer[0]=='O' || answer[0]=='U'
            || answer[0]=='a' || answer[0]=='e' || answer[0]=='i' || answer[0]=='o' || answer[0]=='u')
            {
                answer=track+"L Were you thinking of an "+answer+"?";
                broot->data1=track+"R "+broot->data1;
            }else
            {
                answer=track+"L Were you thinking of a "+answer+"?";
                broot->data1=track+"R "+broot->data1;
            }

            out << answer << endl;
            out << broot->data1 << endl;
            out2 << answer << endl;
            out2 << broot->data1 << endl;

            in.close();
            in2.close();
            out.close();
            out2.close();

            system("CLS");
            for(int i=0;i<20;i++)cout << endl;
            cout << setw(85) << "Thanks! My knowledge has been increased! " << (char)1 << endl << endl;
            Sleep(3500);
        }
    };


    int main()
    {
        char playAgain;

        GuessIt g;
        g.instructions();

        do
        {

            system("CLS");
            for(int i=0;i<15;i++)cout << endl;
            g.SetQuestionsTree();
            g.GameOn();

            system("CLS");
            system("Color F0");
            for(int i=0;i<18;i++)cout << endl;
            cout << setw(69) << "Play again?(y/n)";
            cin >> playAgain;

            if(playAgain=='y')system("CLS");

        }while(playAgain!='n');

        return 0;
    }
