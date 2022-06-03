// Lab4  Poker Game
//Programmer Zakariya Noor
//I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include<iostream>
#include<time.h>
#include<Windows.h>
#include<conio.h>
using namespace std;

void gotoxy(int, int);
void Sort(int[][5], int[][5]);
bool Flush(int[][5], int); 
bool Straight(int[][5], int);
bool HighStraight(int[][5], int);
bool FourOfKind(int[][5], int);
bool ThreeOfKind(int[][5], int);
bool TwoPair(int[][5], int);
bool OnePair(int[][5], int);
void handValueCalc(int&, int[][5], int, int[][5], int&);
void index4Calc(int[][5], int, int&);
void index3Calc(int[][5], int, int&);
void index2Calc(int[][5], int, int&);
void index1Calc(int[][5], int, int&);
void colorChange(int);
void output(int[], int);


int main()
{

    const int SIZE = 5;
    const int CardSize = 52;
    bool play = true;

    cout << "\t\t\t**************************************************************************" << endl;
    cout << "\t\t\t*********************** Welcome to Poker Game*****************************" << endl;
    cout << "\t\t\t**************************************************************************" << endl << endl;
    string s = "";
    cout << "\n\n    Press  (UpperCase 'Y' or LowerCase 'y' ) :\a ";
    cin >> s;
    if (s == "y" || s == "Y")
    {
        int cards[CardSize], dup[CardSize] = { 0 }, //array to hold 52 cards 0-51 and duplicate array to make sure only used once
            i, j, k, number,
            players[SIZE][SIZE], suits[SIZE][SIZE], value, color, tb = 0, winner[SIZE], high, x = 0;
        char replay = ' ';

        do
        {

            srand(time(NULL));

            for (i = 0; i < 52; i++)
                dup[i] = 0;

            for (i = 0; i < 52; i++)
            {
                number = rand() % 52;   // random numbers in 52cards u but only ranging from 0-51

                while (dup[number])     //storing it in duplicate array to check for later
                    number = rand() % 52;//

                cards[i] = number;//
                dup[number]++; //


            }

            k = 0;

            for (i = 0; i < 5; i++) //0-4 5 players
            {
                for (j = 0; j < 5; j++) //5cards
                {
                    number = cards[k];
                    players[i][j] = number % 13; // 0-12 a23456789JQK
                    suits[i][j] = number / 13 + 3; //0-3 diamond,heart, club ,spade
                    k++;
                }
            }

            for (i = 0; i < 5; i++)
            {

                for (j = 0; j < 5; j++)
                {

                    if (players[i][j] > 9)
                    {

                        if (players[i][j] == 10)
                            cout << 'J';
                        else if ((players[i][j] == 11))
                            cout << 'Q';
                        else
                            cout << 'K';
                    }
                    else
                    {
                        if (players[i][j] == 0)
                            cout << 'A';
                        else
                            cout << players[i][j] + 1;
                    }
                    cout << char(suits[i][j]) << ' ';
                }
                cout << endl << endl;
            }

            Sort(players, suits);
            colorChange(13);
            cout << endl;

            system("cls");
            for (i = 0; i < 5; i++)
            {

                cout << "P" << i + 1 << " ";
                for (j = 0; j < 5; j++)
                {
                    if (players[i][j] > 9)
                    {
                        if (players[i][j] == 10)
                            cout << 'J';
                        else if ((players[i][j] == 11))
                            cout << 'Q';
                        else
                            cout << 'K';
                    }
                    else
                    {
                        if (players[i][j] == 0)
                            cout << 'A';
                        else
                            cout << players[i][j] + 1;
                    }
                    cout << char(suits[i][j]) << ' ';
                }
                cout << endl << endl;
            }

            colorChange(15);
            for (i = 0; i < 5; i++)
            {
                if (i == 0)
                {
                    colorChange(11);
                }
                else if (i == 1)
                {
                    colorChange(9);
                }
                else if (i == 2)
                {
                    colorChange(8);
                }
                else if (i == 3)
                {
                    colorChange(13);
                }
                else if (i == 4)
                {
                    colorChange(14);
                }
                //displaying the what player recieved
                cout << "Player " << i + 1 << " flush: " << Flush(suits, i) << " |";
                cout << " straight: " << Straight(players, i) << " ";
                cout << " high straight: " << HighStraight(players, i) << " |";
                cout << " four of kind: " << FourOfKind(players, i) << " |";
                cout << " three of kind: " << ThreeOfKind(players, i) << " |";
                cout << " two pairs: " << TwoPair(players, i) << " |";
                cout << " one pair: " << OnePair(players, i) << " " << endl;
                handValueCalc(value, players, i, suits, tb);
                cout << ": " << value << endl;
                winner[i] = { value };
                colorChange(15);
                cout << endl;
            }

            high = winner[0];
            for (i = 0; i < 5; i++)
            {
                if (high < winner[i])
                {
                    high = winner[i];
                    x = i;
                }
            }

            colorChange(9);




            /*int players_scores[5];

            for(int j= 0; j<5;j++){

                players_scores[j]= players[4][j];

            }*/

            output(winner, high);




            /*cout << "Player " << x + 1 << " holds the winning hand with " << high << " points." << endl;
            cout << endl;*/
            //colorChange(15);
            cout << "Deal again? Y or N?";
            cin >> replay;
        } while (replay == 'Y' || replay == 'y');
    }
    else if (s == "n" || s == "N")
    {
        cout << "Thank You For Playing!!";
    }
    else
    {
        cout << "\n\n\t\t\tPlease Enter (Y) || (N) ONLY: ";
        cin >> s;

    }
    gotoxy(1, 19);
    cout << endl;
    system("cls");
    system("color 30");
    cout << endl << endl;

    cout << "\t***************************" << endl;
    cout << "\t*****Thank You For Playing!!****" << endl;
    cout << "\t***************************" << endl;

    cout << endl;
    system("pause");
    return 0;
}
//****************************************************
//Function to sort the array from ascending order
//****************************************************
void Sort(int TD[][5], int suit[][5])
{
    int i, j, k, maxElement, index, temp;
    for (i = 0; i < 5; i++)
    {
        for (maxElement = 4; maxElement > 0; maxElement--)
        {
            for (index = 0; index < maxElement; index++)
            {
                if (TD[i][index] > TD[i][index + 1])
                {
                    temp = TD[i][index];
                    TD[i][index] = TD[i][index + 1];
                    TD[i][index + 1] = temp;
                    temp = suit[i][index];
                    suit[i][index] = suit[i][index + 1];
                    suit[i][index + 1] = temp;
                }
            }
        }
    }
}
//***************************************************************
//This function will put cursor on x and y axis where you specify
//***************************************************************
void gotoxy(int x, int y)//arguments x axis and y axis
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (INVALID_HANDLE_VALUE != hConsole)
    {
        COORD pos = { x, y };
        SetConsoleCursorPosition(hConsole, pos);
    }
    return;
}
//*****************************************************************
//function to check if its a flush by having all ofthe cards of the
// same suit
// ****************************************************************

bool Flush(int suits[][5], int i)
{
    if ((suits[i][0] == suits[i][1] == suits[i][2] == suits[i][3] == suits[i][4]))
        return true;

    return false;
}

//********************************************************************
// This function will check for for a straight by checking to see if
// the value of the cards are consecutive.
// *******************************************************************

bool Straight(int players[][5], int i)
{
    if ((players[i][0] == players[i][1] - 1) && (players[i][1] == players[i][2] - 1) && (players[i][2] == players[i][3] - 1) && (players[i][3] == players[i][4] - 1))
        return true;

    return false;
}

//************************************************************************
// This function will check for for a Royal flush by checking to see if
// it consist of the following cards 10, jack, queen, king, ace all of the
// same suit
// ***********************************************************************

bool HighStraight(int players[][5], int i)
{
    if ((players[i][0] == 0) && (players[i][1] == 9) && (players[i][2] == 10) && (players[i][3] == 11) && (players[i][4] == 12))
        return true;

    return false;
}

//************************************************************************
// This function will check for a four-of-a-kind by checking for four    
// cards of the same value. *
// ***********************************************************************

bool FourOfKind(int players[][5], int i)
{
    if ((players[i][0] == players[i][1]) && (players[i][1] == players[i][2]) && (players[i][2] == players[i][3]) ||
        (players[i][1] == players[i][2]) && (players[i][2] == players[i][3]) && (players[i][3] == players[i][4]) ||
        (players[i][0] == players[i][2]) && (players[i][2] == players[i][3]) && (players[i][3] == players[i][4]) ||
        (players[i][0] == players[i][1]) && (players[i][1] == players[i][3]) && (players[i][3] == players[i][4]) ||
        (players[i][0] == players[i][1]) && (players[i][1] == players[i][2]) && (players[i][2] == players[i][4]))
        return true;

    return false;
}

//************************************************************************
// This function will check for three cards that are the same number
// ***********************************************************************

bool ThreeOfKind(int players[][5], int i)
{
    if ((players[i][0] == players[i][1]) && (players[i][1] == players[i][2]) ||
        (players[i][1] == players[i][2]) && (players[i][2] == players[i][3]) ||
        (players[i][2] == players[i][3]) && (players[i][3] == players[i][4]) ||
        (players[i][0] == players[i][1]) && (players[i][1] == players[i][3]) ||
        (players[i][0] == players[i][1]) && (players[i][1] == players[i][4]) ||
        (players[i][0] == players[i][2]) && (players[i][2] == players[i][4]) ||
        (players[i][0] == players[i][3]) && (players[i][3] == players[i][4]) ||
        (players[i][0] == players[i][2]) && (players[i][2] == players[i][3]) ||
        (players[i][1] == players[i][3]) && (players[i][3] == players[i][4]) ||
        (players[i][1] == players[i][2]) && (players[i][2] == players[i][4]))
        return true;

    return false;
}
//***************************************************************************
// This function will check for a two pairs by checking for two sets of
// paired cards of the same value and if found will return true else false
//****************************************************************************
bool TwoPair(int players[][5], int i)
{
    if ((players[i][0] == players[i][1]) && (players[i][2] == players[i][3]) ||
        (players[i][0] == players[i][2]) && (players[i][1] == players[i][3]) ||
        (players[i][0] == players[i][3]) && (players[i][1] == players[i][2]) ||
        (players[i][1] == players[i][2]) && (players[i][3] == players[i][4]) ||
        (players[i][1] == players[i][3]) && (players[i][2] == players[i][4]) ||
        (players[i][1] == players[i][4]) && (players[i][2] == players[i][3]) ||
        (players[i][0] == players[i][2]) && (players[i][3] == players[i][4]) ||
        (players[i][0] == players[i][3]) && (players[i][2] == players[i][4]) ||
        (players[i][0] == players[i][4]) && (players[i][2] == players[i][3]) ||
        (players[i][0] == players[i][1]) && (players[i][3] == players[i][4]) ||
        (players[i][0] == players[i][3]) && (players[i][1] == players[i][4]) ||
        (players[i][0] == players[i][4]) && (players[i][1] == players[i][3]) ||
        (players[i][0] == players[i][1]) && (players[i][2] == players[i][4]) ||
        (players[i][0] == players[i][2]) && (players[i][1] == players[i][4]) ||
        (players[i][0] == players[i][4]) && (players[i][1] == players[i][2]))
        return true;

    return false;
}

//*************************************************************************
// This function will check for a single pair of cards of matching values 
// ************************************************************************

bool OnePair(int players[][5], int i)
{
    if (((players[i][0] == players[i][1]) && (players[i][0] != players[i][2])) ||
        ((players[i][1] == players[i][2]) && (players[i][1] != players[i][0]) && (players[i][2] != players[i][3])) ||
        ((players[i][2] == players[i][3]) && (players[i][2] != players[i][1]) && (players[i][3] != players[i][4])) ||
        (players[i][3] == players[i][4]))
        return true;

    return false;

}

//****************************************************************************************************
// This function will check all 9 conditions to win a poker hand in order, by check the
// boolean status of the hand  and then assign a value of that hand to each player
// ***************************************************************************************************

void handValueCalc(int& value, int players[][5], int i, int suits[][5], int& tbreak)
{
    colorChange(10);
    if (HighStraight(players, i) && Flush(suits, i) == true)
    {
        value = 2500000;
        cout << "Royal FLush";
    }
    else if (Straight(players, i) && Flush(suits, i) == true)
    {
        index4Calc(players, i, tbreak);
        value = 1250000 + tbreak;
        cout << "Straight Flush";
    }
    else if (FourOfKind(players, i) == true)
    {
        index3Calc(players, i, tbreak);///234 shared
        value = 625000 + tbreak;
        cout << "Four of a Kind";
    }
    else if (ThreeOfKind(players, i) && OnePair(players, i) == true)
    {
        index2Calc(players, i, tbreak);//second item is always shared
        value = 4000000 + tbreak;
        cout << "Full House";
    }
    else if (Flush(suits, i) == true)
    {
        index4Calc(players, i, tbreak);
        value = 6000000 + tbreak;
        cout << "Flush";
    }
    else if (Straight(players, i) == true)
    {
        index4Calc(players, i, tbreak);
        value = 5000000 + tbreak;
        cout << "Straight";
    }
    else if (ThreeOfKind(players, i) == true)
    {
        index2Calc(players, i, tbreak);
        value = 3000000 + tbreak;
        cout << "Three of a Kind";
    }
    else if (TwoPair(players, i) == true)
    {
        index3Calc(players, i, tbreak);
        value = 2000000 + tbreak;
        cout << "Two Pairs";
    }
    else if (OnePair(players, i) == true)
    {
        index1Calc(players, i, tbreak);
        value = 1000000 + tbreak;
        cout << "One Pair";
    }
    else
    {
        index4Calc(players, i, tbreak);
        value = 0 + tbreak;
        cout << "High Card";
    }
}

//****************************************************************************************************
// This function will check the value of the fifth card and assign the hand a numerical value        
// ***************************************************************************************************
void index4Calc(int players[][5], int i, int& adbreak)
{
    if (players[i][4] == 12)
        adbreak = 8000;
    else if (players[i][4] == 11)
        adbreak = 6000;
    else if (players[i][4] == 10)
        adbreak = 4000;
    else if (players[i][4] == 9)
        adbreak = 2000;
    else if (players[i][4] == 8)
        adbreak = 1000;
    else if (players[i][4] == 7)
        adbreak = 500;
    else if (players[i][4] == 6)
        adbreak = 250;
    else if (players[i][4] == 5)
        adbreak = 125;
    else if (players[i][4] == 4)
        adbreak = 62;
    else if (players[i][4] == 3)
        adbreak = 31;
    else if (players[i][4] == 2)
        adbreak = 15;
    else if (players[i][4] == 1)
        adbreak = 7;
    else
        adbreak = 1;
}

//****************************************************************************************************
// This function will check the value of the fourth and assign the hand a numerical value       
// ***************************************************************************************************
void index3Calc(int players[][5], int i, int& adbreak)
{
    if (players[i][3] == 12)
        adbreak = 8000;
    else if (players[i][3] == 11)
        adbreak = 6000;
    else if (players[i][3] == 10)
        adbreak = 4000;
    else if (players[i][3] == 9)
        adbreak = 2000;
    else if (players[i][3] == 8)
        adbreak = 1000;
    else if (players[i][3] == 7)
        adbreak = 500;
    else if (players[i][3] == 6)
        adbreak = 250;
    else if (players[i][3] == 5)
        adbreak = 125;
    else if (players[i][3] == 4)
        adbreak = 62;
    else if (players[i][3] == 3)
        adbreak = 31;
    else if (players[i][3] == 2)
        adbreak = 15;
    else if (players[i][3] == 1)
        adbreak = 7;
    else
        adbreak = 1;
}

//****************************************************************************************************
// This function will check the value of the third card and assign the hand a numerical value       *
// ***************************************************************************************************
void index2Calc(int players[][5], int i, int& adbreak)
{
    if (players[i][2] == 12)
        adbreak = 8000;
    else if (players[i][2] == 11)
        adbreak = 6000;
    else if (players[i][2] == 10)
        adbreak = 4000;
    else if (players[i][2] == 9)
        adbreak = 2000;
    else if (players[i][2] == 8)
        adbreak = 1000;
    else if (players[i][2] == 7)
        adbreak = 500;
    else if (players[i][2] == 6)
        adbreak = 250;
    else if (players[i][2] == 5)
        adbreak = 125;
    else if (players[i][2] == 4)
        adbreak = 62;
    else if (players[i][2] == 3)
        adbreak = 31;
    else if (players[i][2] == 2)
        adbreak = 15;
    else if (players[i][2] == 1)
        adbreak = 7;
    else
        adbreak = 1;
}
int colorChangeMsg(int i)
{
    if (i == 0)
    {
        colorChange(11);
    }
    else if (i == 1)
    {
        colorChange(9);
    }
    else if (i == 2)
    {
        colorChange(8);
    }
    else if (i == 3)
    {
        colorChange(13);
    }
    else if (i == 4)
    {
        colorChange(14);
    }
    return 0;
}
//****************************************************************************************************************
// This function will check the value of one of the cards in the pair card and assign the hand a number
// ***************************************************************************************************************
void index1Calc(int players[][5], int i, int& assign)
{
    if (players[i][0] == 12 && players[i][1] == 12 || players[i][1] == 12 && players[i][2] == 12 || players[i][2] == 12 && players[i][3] == 12 || players[i][3] == 12 && players[i][4] == 12)
        assign = 8000;
    else if (players[i][0] == 11 && players[i][1] == 11 || players[i][1] == 11 && players[i][2] == 11 || players[i][2] == 11 && players[i][3] == 11 || players[i][3] == 11 && players[i][4] == 11)
        assign = 6000;
    else if (players[i][0] == 10 && players[i][1] == 10 || players[i][1] == 10 && players[i][2] == 10 || players[i][2] == 10 && players[i][3] == 10 || players[i][3] == 10 && players[i][4] == 10)
        assign = 4000;
    else if (players[i][0] == 9 && players[i][1] == 9 || players[i][1] == 9 && players[i][2] == 9 || players[i][2] == 9 && players[i][3] == 9 || players[i][3] == 9 && players[i][4] == 9)
        assign = 2000;
    else if (players[i][0] == 8 && players[i][1] == 8 || players[i][1] == 8 && players[i][2] == 8 || players[i][2] == 8 && players[i][3] == 8 || players[i][3] == 8 && players[i][4] == 8)
        assign = 1000;
    else if (players[i][0] == 7 && players[i][1] == 7 || players[i][1] == 7 && players[i][2] == 7 || players[i][2] == 7 && players[i][3] == 7 || players[i][3] == 7 && players[i][4] == 7)
        assign = 500;
    else if (players[i][0] == 6 && players[i][1] == 6 || players[i][1] == 6 && players[i][2] == 6 || players[i][2] == 6 && players[i][3] == 6 || players[i][3] == 6 && players[i][4] == 6)
        assign = 250;
    else if (players[i][0] == 5 && players[i][1] == 5 || players[i][1] == 5 && players[i][2] == 5 || players[i][2] == 5 && players[i][3] == 5 || players[i][3] == 5 && players[i][4] == 5)
        assign = 125;
    else if (players[i][0] == 4 && players[i][1] == 4 || players[i][1] == 4 && players[i][2] == 4 || players[i][2] == 4 && players[i][3] == 4 || players[i][3] == 4 && players[i][4] == 4)
        assign = 62;
    else if (players[i][0] == 3 && players[i][1] == 3 || players[i][1] == 3 && players[i][2] == 3 || players[i][2] == 3 && players[i][3] == 3 || players[i][3] == 3 && players[i][4] == 3)
        assign = 31;
    else if (players[i][0] == 2 && players[i][1] == 2 || players[i][1] == 2 && players[i][2] == 2 || players[i][2] == 2 && players[i][3] == 2 || players[i][3] == 2 && players[i][4] == 2)
        assign = 15;
    else if (players[i][0] == 1 && players[i][1] == 1 || players[i][1] == 1 && players[i][2] == 1 || players[i][2] == 1 && players[i][3] == 1 || players[i][3] == 1 && players[i][4] == 1)
        assign = 7;
    else
        assign = 1;
}

//************************************************
// This function changes the text color         *
// ***********************************************

void colorChange(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

//***********************************************************
//Function to show and compare who wins or ties
//***********************************************************

void output(int player[], int maximum) {

    int next, champ[5] = { 0 };

    for (int i = 0; i < 5; i++) {

        next = player[i];
        if (next > maximum)
            maximum = next;
    }

    int index = 0;

    for (int i = 0; i < 5; i++) {

        if (player[i] == maximum) {
            champ[i] = i + 1;               // will assign the player number which has the maximum score.
            index++;
        }                                   // All other corresponding spaces/players numbers will store a 0.
    }


    if (index > 1) {
        for (int i = 0; i < 5; i++) {

            if (champ[i] != 0)
                cout << "Player " << champ[i] << ",";
        }


        cout << " have a tie on " << maximum << " points.\n\n\n";
        colorChange(15);
    }

    else {
        for (int i = 0; i < 5; i++) {

            if (champ[i] != 0) {
                cout << "Player " << champ[i] << " holds the winning hand with " << maximum << " points.\n\n\n";
                colorChange(15);
            }
        }



    }
}

