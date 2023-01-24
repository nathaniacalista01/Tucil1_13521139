#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

void createNewArray(int row, int col, char answer[row][col]){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col;j++){
            answer[i][j] = '#';
        }
    }
}

/* Prosedur untuk menambahkan sebuah elemen ke dalam matriks dua dimensi */
void insertFirst(int row,int col,char answer[row][col],char items[col]){
    int i = 0;
    int found = 0;  
    while(found == 0 && i < row){
        for(int j = 0; j < col;j++){
            if(answer[i][j] =='#'){
                answer[i][j] = items[j];
                found = 1;
            }
        }
        i += 1;
    }
}

/* Mencari semua kemungkinan operasi yang ada  */
void allCombinations(char items[4], char data[3], int last, int index, char answer[64][3],int count){
    for(int i = 0; i < 4;i++){
        data[index] = items[i];
        if(index == last){
            insertFirst(64,3,answer,data);
        }else{
            allCombinations(items,data,last,index+1,answer,count);
        }
    }
}

void operators(char answer[64][3]){
    char items[4] = {'*','+','/','-'};
    char data[3] = {' ',' ',' '};
    createNewArray(64,4,answer);
    allCombinations(items,data,2,0,answer,0);
}

/* Prosedur bawaan yang membantu dalam menukar dua elemen dalam sebuah matriks */
void swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//permutation function
void permutation(char arr[4], int start, int end, char answers[24][4])
{
    if(start==end)
    {
        insertFirst(24,4,answers,arr);
        return;
    }
    int i;
    for(i=start;i<=end;i++)
    {
        swap(&arr[i], &arr[start]);
        permutation(arr, start+1, end,answers);
        swap(&arr[i] ,&arr[start]);
    }
}

void cardCombinations(char cards[4], char results[24][4]){
    createNewArray(24,4,results);
    permutation(cards,0,3,results);
}

/* Fungsi bantuan untuk menapilkan operasi yang dibuat */

/* Menggabungkan kartu dan operasi yang ada menjadi satu operasi */
void createOperations(char cards[4], char operators[3], char operations[7]){
    operations[0] = cards[0];
    int operatorsCount = 0; 
    int cardsCount= 1;
    int i = 1; 
    while(i < 7){
        if(i%2==0){
            operations[i] = cards[cardsCount];
            cardsCount += 1;
        }
        else{
            operations[i] = operators[operatorsCount];
            operatorsCount+= 1;
        }
        i += 1;
    }
}

void createAllOperations(char cards[24][4],char operators[64][3],char allOperations[1536][7]){
    createNewArray(1536,7,allOperations);
    for(int i = 0 ; i < 24; i++){
        for(int j = 0; j < 64;j++){
            char operations[7];
            createOperations(cards[i],operators[j],operations);
            insertFirst(1536,7,allOperations,operations);
        }
    }
}

float charToFloat(char c){
    if(c == 'A'){
        return 1.0;
    }else if(c == 'J'){
        return 11.0;
    }else if(c == 'Q'){
        return 12.0;
    }else if(c == 'K'){
        return 13.0;
    }else if(c == '0'){
        return 10.0;
    }else{
        return (float)((int)c-48);
    }
}

float calculate(float first, char ops, float sec){
    switch (ops)
    {
    case ('+'):
        return first + sec;
        break;
    case ('-'):
        return first - sec;
    case ('*'):
        return first * sec;
    case ('/'):
        if(sec == 0){
            return -9999;
        }
        return first/sec;
    }
}

void insertResults(int row,char results[][11],char items[11]){
    for(int i = 0; i<11;i++){
        results[row][i] = items[i];
    }
}

void parantheses(char operations[7],char results[5][11], float counts[5]){
    float firstNum = charToFloat(operations[0]);
    float secondNum = charToFloat(operations[2]);
    float thirdNum = charToFloat(operations[4]);
    float fourthNum = charToFloat(operations[6]);
    /* Equation pertama */
    char first[11] = {'(','(',operations[0],operations[1],operations[2],')',operations[3],operations[4],')',operations[5],operations[6]};
    counts[0] = calculate(calculate(calculate(firstNum,operations[1],secondNum),operations[3],thirdNum),operations[5],fourthNum);
    // printf("%.2f\n",counts[0]);
    insertResults(0,results,first);

    /* Persamaan kedua  */
    char second[11] = {'(',operations[0],operations[1],'(',operations[2],operations[3],operations[4],')',')',operations[5],operations[6]};
    insertResults(1,results,second);
    counts[1] = calculate(calculate(firstNum,operations[1],calculate(secondNum,operations[3],thirdNum)),operations[5],fourthNum);
    // printf("%.2f",counts[1]);

    /* Persamaan ketiga */
    char third[11] = {'(',operations[0],operations[1],operations[2],')',operations[3],'(',operations[4],operations[5],operations[6],')'};
    insertResults(2,results,third);
    counts[2] = calculate(calculate(firstNum,operations[1],secondNum),operations[3],calculate(thirdNum,operations[5],fourthNum)); 
    // printf("%.2f",counts[2]);

    /* Persamaan keempat */
    char fourth[11] = {operations[0],operations[1],'(','(',operations[2],operations[3],operations[4],')',operations[5],operations[6],')'};
    insertResults(3,results,fourth);
    counts[3] = calculate(firstNum,operations[1],calculate(calculate(secondNum,operations[3],thirdNum),operations[5],fourthNum));

    /* Persamaan kelima */
    char fifth[11] = {operations[0],operations[1],'(',operations[2],operations[3],'(',operations[4],operations[5],operations[6],')',')'};
    insertResults(4,results,fifth);
    counts[4] = calculate(firstNum,operations[1],calculate(secondNum,operations[3],calculate(thirdNum,operations[5],fourthNum)));
}

int isDuplicate(char answers[7680][11], char results[11]){
    for(int i = 0; i < 7680; i++){
        int count = 0; 
        int j = 0; 
        while(answers[i][j] == results[j] && j < 11){
            j += 1;     
        }
        if(j == 11){
            return 1;
        }
    }
    return 0;
}

int searchResults(char allOperations[1536][7], char answers[7680][11]){
    int answer = 0;

    for(int i = 0; i < 1536; i++){
        char results[5][11];
        float counts[5];
        parantheses(allOperations[i],results,counts);
        for(int j = 0; j < 5 ; j++){
            if(counts[j] == 24.00){
                // if(isDuplicate(answers,results[j]) == 0){
                //     insertFirst(7680,11,answers,results[j]);
                //     showSolutions(results[j]);
                //     printf("\n");
                //     answer += 1;
                // }
                insertFirst(7680,11,answers,results[j]);                
                answer += 1;
            }
        }
    }
    return answer;
}


int checkUserInput(char temp[2]){
    if((int)temp[1] != 0){
        if(temp[1] == '0' && temp[0] == '1'){
            return 1;
        }else{
            return 0;
        };
    }else{
        if(temp[0] == 'K' || temp[0] == 'Q' || temp[0] == 'J' || temp[0] == 'A'){
            return 1;
        }else if((int)temp[0] >= 50 && (int)temp[0] <= 57){
            return 1;
        }else{
            return 0;
        }
    }
}

int displayMenu(){
    int options;
    do
    {
        printf("============== Welcome to ==============\n");
        printf("============ 24 Game Solver ============\n");
        printf("========================================\n");
        printf("Silakan masukkan nomor menu yang anda inginkan : \n");
        printf("1. Memasukkan kombinasi kartu secara sendiri  \n");
        printf("2. Merandom kombinasi kartu  \n");
        printf("3. Keluar \n");
        scanf("%d",&options);
        getchar();
    } while (options != 1 && options != 2 && options != 3);
    
    return options ;
}

int inputUser(char cards[4]){
    char allInputs[12];
    printf("Silakan memasukkan kombinasi kartu anda :");
    fgets(allInputs,12,stdin);
    int i = 0; 
    int cardsIndex = 0;
    while(i < 12 && (int) allInputs[i] != 0){
        char temp[2];
        int count = 0; 
        while((int)allInputs[i] != 32 && (int) allInputs[i] != 0 && allInputs[i] != '\n'){
            count += 1;
            i += 1;
        }
        if(count >= 3){
            return 0;
        }else if(count == 2){
            char val[2] = {allInputs[i-2],allInputs[i-1]};
            if(checkUserInput(val) == 0){
                return 0;
            }else{
                if(cardsIndex <= 3){
                    cards[cardsIndex] = '0';
                    cardsIndex += 1;
                }else{
                    return 0;
                }
            }
        }else{
            temp[0] = allInputs[i-1];
            if(checkUserInput(temp) == 1){
                if(cardsIndex <= 3){
                    cards[cardsIndex] = temp[0];
                    cardsIndex += 1;
                }else{
                    return 0;
                }
            }else{
                return 0;
            };        
        }
        i += 1;
    }
    if(cardsIndex <4){
        return 0;
    }
    return 1;
}

void cardRandomizer(char cards[4]){
    for(int i =0; i<4;i++){
        int temp = rand()%12 + 1;
        switch (temp)
        {
            case 1 :
                cards[i] = 'A';
                break;
            case 10 : 
                cards[i] = '0';
                break;
            case 11 : 
                cards[i] = 'J';
                break;
            case 12 : 
                cards[i] = 'Q';
                break;
            case 13 :
                cards[i] = 'K';
                break;
            default:
                char val = temp + '0';
                cards[i] = val;
        }
    }
}

void exitMsg(){
    printf("======= Terima Kasih Sudah Bermain =======\n");
    printf("==========================================");
}
void printAnswers(char answers[7680][11]){
    int empty = 0; 
    int i = 0; 
    while(i < 7680 && empty == 0){
        for(int j = 0; j < 11; j++){
            if(answers[i][j] == '#'){
                empty = 1;
                break;
            }else{
                if(answers[i][j] == '0'){
                    printf("10 ");
                }else{
                    printf("%c ",answers[i][j]);
                }
            }
        }
        printf("\n");
        i+= 1;
    }
}

void saveFile(char answers[7680][11]){
    int options = 0;
    while(options != 1 && options != 2){
        printf("========== Apakah anda mau menyimpan jawaban ini? ==========\n");
        printf("Ketik 1 jika mau dan 2 jika tidak mau\n");
        scanf("%d",&options);
    }
    if(options == 1){
        char filename[100];
        FILE *fptr;
        fptr = NULL;
        while(fptr == NULL){
            printf("============== Masukkan nama file (file.txt) ==============\n");
            scanf("%s",&filename);
            fptr = fopen(filename,"w");
        }
        int empty = 0; 
        int i = 0; 
        while(i < 7680 && empty == 0){
            for(int j = 0; j < 11; j++){
                if(answers[i][j] == '#'){
                    empty = 1;
                    break;
                }else{
                    if(answers[i][j] == '0'){
                        fprintf(fptr,"10 ");
                    }else{
                        fprintf(fptr,"%c ",answers[i][j]);
                    }
                }
            }
            fprintf(fptr,"\n");
            i+= 1;
        } 
        fclose(fptr);
        printf("===================== DONE ===================\n");
        exitMsg();
    }else{
        exitMsg();
    }   
}

void calculateCard(char cards[4]){
    char allOperators[64][3];
    char allCardsCombinations[24][4];
    char allOperations[1536][7];
    char answers[7680][11];
  
    // Current time
    struct timeval begin, end;
    gettimeofday(&begin, 0);

    createNewArray(7680,11,answers);
    /* Mendapatkan semua kombinasi kartu  */
    cardCombinations(cards,allCardsCombinations);
    
    /* Mendapatkan semua kombinasi dari operator */
    operators(allOperators);
    /* Membuat semua kemungkinan operasi yang ada */
    createAllOperations(allCardsCombinations,allOperators,allOperations);
    int totalAnswer  = searchResults(allOperations,answers);
    gettimeofday(&end,0);
    float microseconds = end.tv_usec - begin.tv_usec;
    if(totalAnswer == 0){
        printf("=========== Tidak ada solusi yang memenuhi ===========");
    }else{
        printf("Solusi yang memenuhi ada sebanyak \n");
        printf("%d\n",totalAnswer);
        printAnswers(answers);
        printf("Waktu yang diperlukan : ");
        printf("%.2f microseconds \n",microseconds);
        saveFile(answers);
    }
}



int main(){
    char cards[4];
    int options = displayMenu();
    if(options == 1){
        int temp = inputUser(cards);
        while (temp == 0){
            printf("Input anda masih kurang tepat, silakan coba lagi!\n");
            temp = inputUser(cards);
        }
        calculateCard(cards);
    }else if(options == 2){
        cardRandomizer(cards);
        calculateCard(cards);
    }else{
        exitMsg();
    }
    
    return 0;
}

