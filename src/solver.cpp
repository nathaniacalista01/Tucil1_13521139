#include <iostream>
using namespace std;
#include <fstream>
using std::ofstream;
#include <chrono>
#include <time.h>

void welcomeMsg(){
    cout << " __________________________________________________________" <<endl;
    cout << "|          _____________         __        __              |" <<endl;
    cout << "|         |____________ |       |  |      |  |             |" <<endl;
    cout << "|                     | |       |  |      |  |             |" <<endl;
    cout << "|                     | |       |  |      |  |             |" <<endl;
    cout << "|         ____________| |       |  |______|  |             |" <<endl;
    cout << "|        | | ___________|       |__________  |             |" <<endl;
    cout << "|        | |                              |  |             |" <<endl;  
    cout << "|        | |                              |  |             |" <<endl;
    cout << "|        | |____________                  |  |             |" <<endl;
    cout << "|        |______________|                 |__|             |" <<endl;
    cout << "| ________________________________________________________ |" <<endl;
    cout << "\n" <<endl;
}

void createEmptyArray(int length, string *results){
    for(int i = 0; i < length;i++){
        results[i] = "#";
    }
}

void insertFirst(int length, string *answers, string items){
    int i =0; 
    while(true && i < length){
        if(answers[i] == "#"){
            answers[i] = items;
            break;
        }
        i += 1;
    }
}

int displayMenu(){
    int options;
    while(true){
        cout << "=================== Welcome to ===================" <<endl;
        cout << "================== 24 Game Solver==================" <<endl;
        cout << "===================================================" <<endl;
        cout << "Silakan masukkan nomor menu yang anda ingingkan : " <<endl;
        cout << "1. Memasukkan kombinasi kartu secara manual" <<endl;
        cout << "2. Mengambil angka random " <<endl;
        cout << "3. Keluar " <<endl;
        cin >> options;
        if(options == 1 || options == 2 || options == 3){
            break;
        }
    }
    return options;
}

void swapCards(string *a, string *b){
    string temp; 
    temp = *a;
    *a = *b;
    *b = temp;
}

void permutation(string &cards, int start, int lastIndex, string results[]){
    if(start == lastIndex){
        insertFirst(24,results,cards);
        return;
    }
    for(int i = start; i <= lastIndex;i++){
        swap(cards[start],cards[i]);
        permutation(cards,start+1,lastIndex,results);
        swap(cards[start],cards[i]);
    }
}

void cardCombination(string card,string results[24]){
    createEmptyArray(24,results);
    permutation(card,0,3,results);
}

void allCombinations(string operators, string answer[64]){
    for(int i = 0; i < 4 ; i++){
        string temp = "###";
        temp[0] = operators[i];
        for(int j = 0; j< 4;j++){
            temp[1] = operators[j];
            for(int k = 0; k < 4;k++){
                temp[2] = operators[k];
                insertFirst(64,answer,temp);
            }  
        }
    }
}

void operators(string answer[64]){
    string operators = "*+-/";
    createEmptyArray(64,answer);
    allCombinations(operators,answer);
}

string getOperations(string operators, string card){
    string results = "#######";
    results[0] = card[0];
    int i = 1; int cardsCount = 1; int operatorsCount = 0;
    while(i < 7){
        if(i%2 == 0){
            results[i] = card[cardsCount];
            cardsCount += 1;
        }else{
            results[i] = operators[operatorsCount];
            operatorsCount += 1;
        }
        i += 1;
    }
    return results;
}

void getAllOperations(string cards[24], string operators[64], string operations[1536]){
    createEmptyArray(1536,operations);
    for(int i = 0; i < 24; i++){
        for(int j = 0; j < 64; j ++){
            string results = getOperations(operators[j],cards[i]);
            insertFirst(1536,operations,results);
        }
    }
}

bool isValid(string cards[4]){
    for(int i =0; i < 4;i++){
        if(cards[i] != "A" && cards[i] != "Q" && cards[i] != "J"&& cards[i] != "K"&& cards[i] != "9"&&cards[i] != "8"&& 
        cards[i] != "7"&& cards[i] != "6"&& cards[i] != "5"&& cards[i] != "4"&& cards[i] != "3"&& cards[i] != "2" ){
            if(cards[i] == "10"){
                cards[i] = "0";
            }else{
                cout << "Input masih salah di kartu ";
                cout << cards[i] <<endl;
                return false;
            }
            
        }
    }
    return true;
}

string randomizeCard(){
    string results = "####";
    srand(time(0));
    for(int i = 0; i < 4; i++){
        int temp = rand()%12 + 1;
        if(temp == 1){
            results[i] = 'A';
        }else if(temp == 10){
            results[i] = '0';
        }else if(temp == 11){
            results[i] = 'J';
        }else if(temp == 12){
            results[i] = 'Q';
        }else if (temp == 13){
            results[i] = 'K';
        }else{
            results[i] = temp + '0';
        }
    }
    cout << "Kartu yang anda dapat : " <<endl;
    for(int i = 0; i < 4; i++){
        cout << results[i] << " ";
    }
    cout << "\n";
    return results;
}

string userInput(string cards[4]){
    bool allValid = true;
    string card;
    do
    {
        cout << "Masukkan kombinasi kartu yang anda inginkan : " <<endl;
        cin >> cards[0] >> cards[1] >>cards[2] >>cards[3];
        allValid = isValid(cards);
        card = "";
        for(int i =0; i < 4;i++){
            card += cards[i];
        }
    } while (!allValid);
    return card;
}

float charToNum(char c){
    switch (c){
    case 'A':
        return 1.0;
        break;
    case 'J':
        return 11.0;
        break;
    case 'Q' :
        return 12.0;
        break;
    case 'K' : 
        return 13.0; 
        break;
    case '0':
        return 10.0;
        break;
    default:
        return (float)((int)c - 48);
        break;
    }
}

float calculate(float first, char ops, float sec){
    switch (ops){
    case '+':
        return first + sec;
        break;
    case '-':
        return first - sec;
        break;
    case '/':
        if(sec == 0){
            return -9999.0;
        }
        return first/sec;
        break;
    default:
        return first*sec;
        break;
    }
}

void parantheses(string operations, float count[5], string results[5]){
    float firstNum = charToNum(operations[0]);
    float secondNum = charToNum(operations[2]);
    float thirdNum = charToNum(operations[4]);
    float fourthNum = charToNum(operations[6]);

    results[0] =  {'(','(',operations[0],operations[1],operations[2],')',operations[3],operations[4],')',operations[5],operations[6]};
    count[0] = calculate(calculate(calculate(firstNum,operations[1],secondNum),operations[3],thirdNum),operations[5],fourthNum);
    
    results[1] = {'(',operations[0],operations[1],'(',operations[2],operations[3],operations[4],')',')',operations[5],operations[6]};
    count[1] = calculate(calculate(firstNum,operations[1],calculate(secondNum,operations[3],thirdNum)),operations[5],fourthNum);

    results[2] = {'(',operations[0],operations[1],operations[2],')',operations[3],'(',operations[4],operations[5],operations[6],')'};
    count[2] = calculate(calculate(firstNum,operations[1],secondNum),operations[3],calculate(thirdNum,operations[5],fourthNum)); 

    results[3]= {operations[0],operations[1],'(','(',operations[2],operations[3],operations[4],')',operations[5],operations[6],')'};
    count[3] = calculate(firstNum,operations[1],calculate(calculate(secondNum,operations[3],thirdNum),operations[5],fourthNum));

    /* Persamaan kelima */
    results[4] = {operations[0],operations[1],'(',operations[2],operations[3],'(',operations[4],operations[5],operations[6],')',')'};
    count[4] = calculate(firstNum,operations[1],calculate(secondNum,operations[3],calculate(thirdNum,operations[5],fourthNum)));
}

void exitMsg(){
    cout << "============= Terima kasih sudah bermain =============" <<endl;
}

void displayAnswer(string finalAnswers[1000]){
    int i = 0; 
    bool empty = false;
    while(finalAnswers[i] != "#" && !empty){
        if(finalAnswers[i] == "#"){
            empty = true;
        }else{
            for(int j = 0; j < 11; j++){
                if(finalAnswers[i][j] == '0'){
                    cout << "10 ";
                }else{
                    cout << finalAnswers[i][j] << " ";
                }
            }
            cout << "\n";
        }
        i += 1;
    }
}

void saveFile(string finalAnswers[1000]){
    int options;
    while(true){
        cout << "Apakah anda mau menyimpan jawaban anda? "<<endl;
        cout << "Ketik 1 jika mau dan 2 jika tidak " <<endl;
        cin >> options;
        if(options == 1 || options == 2){
            break;
        }else{
            cout << "Input anda masih kurang tepat, silakan ulangi lagi!" <<endl;
        }
    }
    if(options == 1){
        string fileName; 
        cout << "Masukkan nama file yang anda inginkan (tanpa .txt) " <<endl;
        fstream newFile; 
        cin >> fileName;
        newFile.open("../test/" + fileName + ".txt",ios::out);
        if(newFile.is_open()){
            int i = 0; 
            bool empty = false;
            while(finalAnswers[i] != "#" && !empty){
                if(finalAnswers[i] == "#"){
                    empty = true;
                }else{
                    for(int j = 0; j < 11; j++){
                        if(finalAnswers[i][j] == '0'){
                            newFile << "10 ";
                        }else{
                            newFile << finalAnswers[i][j] << " ";
                        }
                    }
                    newFile << "\n";
                }
                i += 1;
            }
        }else{
            cout << "Tidak bisa membuka file "<<endl;
        }
    }else{
        exitMsg();
    }
}

bool isDuplicate(string answers[1000],string results){
    bool empty = false;
    int i = 0; 
    while(!empty && i < 1000){
        if(answers[i] == results){
            return true;
        }else if(answers[i] == "#"){
            empty = true;
        }
        i += 1;
    }
    return false;
}

void calculateCard(string card){
    string allCardsCombination[24];
    string allOperators[64];
    string allOperations[1536];
    
    string finalAnswers[1000];
    int totalAnswer = 0;
    auto start = chrono :: high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
  
    /* Semua kombinasi kartu (ada 24) */
    cardCombination(card,allCardsCombination);
    /* Semua permutasi dari operators dengan repetisi (ada 64) */
    operators(allOperators);

    getAllOperations(allCardsCombination,allOperators,allOperations);
    createEmptyArray(1000,finalAnswers);
    for(int i = 0; i < 1536; i++){
        float count[5];
        string results[5];
        parantheses(allOperations[i],count,results);
        for(int j = 0; j < 5; j++){
            if(count[j] == 24.00){
                if(!isDuplicate(finalAnswers,results[j])){
                    insertFirst(1000,finalAnswers,results[j]);
                    totalAnswer += 1;
                }
            }
        }
    }
    auto end = chrono :: high_resolution_clock :: now();
    double duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    duration *= 1e-9;

    cout << "Ada sebanyak ";
    cout << totalAnswer;
    cout << " solusi yang ditemukan "<<endl;
    displayAnswer(finalAnswers);
    cout << "Time taken by program is : " << fixed << duration << " seconds" <<endl;
    if(totalAnswer != 0){
        saveFile(finalAnswers);
    }else{
        exitMsg();
    }
    
}

int main(){
    string cards[4];
    welcomeMsg();
    int options = displayMenu();
    if(options == 1){
        string card = userInput(cards);
        calculateCard(card);
    }else if(options == 2){
        string card = randomizeCard();
        calculateCard(card);
    }else{
        exitMsg();
    }
    return 0;
}