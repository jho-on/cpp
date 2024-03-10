#include <iostream>
#include <ctime>
#include <cmath>
#include <windows.h>
#include <algorithm>


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using str = std::string;
const int HEADERLEN = 51;
const str HEADERCHARS[2] = {"-", "="};

str playerName;
double playerMaxLife = 4.0;
double playerLife = 4.0;
double playerDefense = 0.0;
double playerDamage = 1.0;
int coins = 0;

str monsterName = "Monster";
double monsterMaxLife = 2.0;
double monsterLife = 2.0;
double monsterDefense = 1.0;
double monsterDamage = 1.0;
int coinDrop = 2;

int upArmorPrice = 2;
int upSwordPrice = 2;
int upMaxLifePrice = 2;
int restoreHealthPrice = 2;

bool turn = rand() % 2;


void menu();

/**
 * Make color to use in text displayed in console
 * 
 * @param textColor Color of the text
 * @param BGColor Color of the background of the text
 * @return Return the integer representing the color and background especified
*/
int getColor(int textColor = 15, int BGColor = 0){
    int color =  textColor + (BGColor * 16);
    return color;
}

/**
 * Edit and display some text in the console
 * 
 * @param text The text to be displayed
 * @param time The time, in seconds, that the code should sleep after printing the line
 * @param header If true a decoration will be added to the text
 * @param breakBefore Break line before displaying
 * @param breakAfter Break line after displaying
*/
void print(str text, int color=15, double time = .5, bool breakBefore = false, bool header = false, bool breakAfter = true){
    if (breakBefore){
        std::cout << "\n";
    }

    SetConsoleTextAttribute(hConsole, getColor(color));
    if (header){
        int textSize = text.size();
        str header = "";
        str newText = "";
        int charNow = 0;

        for (int i = ceil((HEADERLEN - textSize)/2); i > 0; i--){
            header.append(HEADERCHARS[charNow]);
            (charNow > 0) ? charNow-- : charNow++;
        }
        
        newText.append(header);
        newText.append(text);
        reverse(header.begin(), header.end());
        newText.append(header);

        std::cout << newText;

        /*for (int i = ceil((HEADERLEN - textSize)/2); i > 0; i--){
            (charNow > 0) ? charNow-- : charNow++;
            newText.append(HEADERCHARS[charNow]);
        }*/
        

    }else{
        std::cout << text;
    }

    Sleep(time * 1000);

    SetConsoleTextAttribute(hConsole, getColor(15));

    if (breakAfter){
        std::cout << "\n";
    }
}


void getPlayerName(){
    std::cout << "Username: ";
    std::cin >> playerName;
}


void shop(){
    int choice;
    print("SHOP", getColor(9, 15), 1.0, true, true);

    print("Your coins: " + std::to_string(coins));
    print("1. " + std::to_string(upArmorPrice) + " coins | +0.5 defense");
    print("2. " + std::to_string(upSwordPrice) + " coins | +1 damage");
    print("3. " + std::to_string(upMaxLifePrice) + " coins | +1 life");
    print("4. " + std::to_string(restoreHealthPrice) + " coins | Restore health");
    print("5. Leave");
    
    print("What you want to do?: ", 10, .5, false, false, false);
    std::cin >> choice;

    switch(choice){
        case 1:
            if (coins >= upArmorPrice){
                coins -= upArmorPrice;
                upArmorPrice *= 2;
                playerDefense += 0.5;
            }else{
                std::cout << "You dont have enought coins to by this!!!\n";
            }
            break;
        case 2:
            if (coins >= upSwordPrice){
                    coins -= upSwordPrice;
                    upSwordPrice *= 2;
                    playerDamage += 1;
            }else{
                std::cout << "You dont have enought coins to by this!!!\n";
            }
            break;
        case 3:
            if (coins >= upMaxLifePrice){
                    coins -= upMaxLifePrice;
                    upMaxLifePrice *= 2;
                    playerMaxLife += 1;
            }else{
                std::cout << "You dont have enought coins to by this!!!\n";
            }
            break;
        case 4:
            if (coins >= restoreHealthPrice){
                coins -= restoreHealthPrice;
                restoreHealthPrice *= 2;
                playerLife = playerMaxLife;
            }else{
                std::cout << "You dont have enought coins to by this!!!\n";
            }
            break;
        case 5:
            menu();
            break;
        default:
            std::cout << "Type a valid number!!!\n";
            break;
    }
    shop();
}


void battle(){
    while(true){
   
        if (playerLife > 0 && monsterLife > 0){
            if (turn){
                int choice;
                print("                  [PLAYER TURN]                   ", getColor(0, 11), 1.0);
                print("BATTLE", getColor(9, 15), .5, false, true);
                print(playerName, 11, 0);
                print("Life: " + std::to_string((int)playerLife), 11);

                print(monsterName, 12, 0, true);
                print("Life: " + std::to_string((int)monsterLife), 12);
                print("--------------------------------------------------", getColor(9, 15), 1.0, false);
               
                print("1. Attack");
                print("2. Defend");
                print("What you want to do?: ", 10, .5, 0, 0, 0);
                std::cin >> choice;

                if (choice == 1){
                    monsterLife -= playerDamage;
                }else if (choice == 2){
                    playerLife += playerDefense;
                }
                turn = false;

            }else{
                bool action = rand() % 2;
                print("                   [ENEMY TURN]                   ", getColor(0, 12), 1.0);

                print("BATTLE", getColor(9, 15), .5, false, true);
                print(playerName, 11, 0);
                print("Life: " + std::to_string((int)playerLife), 11);

                print(monsterName, 12, 0, true);
                print("Life: " + std::to_string((int)monsterLife), 12);
                print("--------------------------------------------------", getColor(9, 15), 1, false, true);

                if (action){
                    print(monsterName + " chose attack", getColor(0, 12));
                    playerLife -= monsterDamage;
                }else{
                    print(monsterName + " chose defend", getColor(0, 12));
                    monsterLife += monsterDefense;
                }
                turn = true;
            }
        }else{
            if (playerLife <= 0){
                print("#####################################", 12, 0, 1, 0);
                print("#############[GAME OVER]#############", 12, 0);
                print("#####################################", 12, 2, 0, 0, 1);
                exit(0);
            }else if (monsterLife <= 0){
                print("WIN", getColor(0, 14), 0, 0, true);
                print("You earn " + std::to_string(coinDrop) + " coins", getColor(0, 14), 1);
                coins += coinDrop;
                monsterLife = pow(2, monsterMaxLife);
                monsterMaxLife += 1;
                monsterDefense += 0.5;
                coinDrop *= 2;
                menu();
                
            }
        }
    }
}


void status(){
    print("STATUS", getColor(9, 15), 1.0, true, true);
    print("Name: " + playerName);
    print("Max Life: " + std::to_string((int) playerMaxLife));
    print("Life: " + std::to_string((int) playerLife));
    print("Defense: " + std::to_string((int) playerDefense));
    print("Damage: " + std::to_string((int) playerDamage));
    print("Coins: " + std::to_string(coins));
}


void menu(){
    int choice;
    
    print("MENU", getColor(9, 15), 1.0, true, true);
    print("1. Shop");
    print("2. Battle");
    print("3. Status");
    print("What you want to do?: ", 10, 0, false, false, false);
    std::cin >> choice;

    switch(choice){
        case 1:
            shop();
            break;
        case 2:
            battle();
            break;
        case 3:
            status();
            Sleep(.5 * 1000);
            menu();
            break;
    }
}


int main(){
    srand(time(NULL));

    getPlayerName();
    menu();


    return 0;
}