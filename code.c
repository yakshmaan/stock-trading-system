#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX_USERS 100
#define MAX_STOCKS 20
#define MAX_PORTFOLIO 50
#define MAX_TRANSACTIONS 500
#define MAX_NAME 50

typedef struct{
    char symbol[10];
    int quantity;
    float avg_buy_price;
}PortfolioItem;

typedef struct{
    char username[MAX_NAME];
    char password[MAX_NAME];
    float balance;
    bool is_logged_in;
    bool is_admin;
    PortfolioItem portfolio[MAX_PORTFOLIO];
    int portfolio_count;
}User;

typedef struct{
    char symbol[10];
    char company_name[MAX_NAME];
    float price;
}Stock;

typedef struct{
    int id;
    char username[MAX_NAME];
    char symbol[10];
    char type[10];  
    int quantity;
    float price;
    float total;
    char date[30];
}Transaction;


//global variable//

Transaction transactions[MAX_TRANSACTIONS];
int transaction_count = 0;
User users[MAX_USERS];
int user_count = 0;
User *current_user = NULL;

Stock stocks[MAX_STOCKS];
int stock_count = 0;

void register_user();
void login();
void display_menu();
void initialize_stocks(); 
void view_stocks();
void create_admin();
void clear_input_buffer();
void add_new_stock();
void view_all_users();
void buy_stock();
void sell_stock();
void view_portfolio();
Stock* find_stock_by_symbol(char *symbol);
void add_money();
void withdraw_money();
void add_transaction(char *symbol,char *type,int quantity,float price);
void view_transactions();
void save_data();
void load_data();

int main(){
    int choice;
    
    printf("\n╔════════════════════════════════════════════════╗\n");
    printf("║     WELCOME TO C TRADING PLATFORM v1.0        ║\n");
    printf("╚════════════════════════════════════════════════╝\n");

    load_data();
    initialize_stocks();
    create_admin();
    
    
    while(1){
        if (current_user == NULL){
            display_menu();
        }
        else{
            // Check if admin or regular user
            if(current_user->is_admin) {
                // ADMIN MENU
                printf("\n==============================\n");
                printf("| ADMIN: %-20s|\n", current_user->username);
                printf("| BALANCE: $%-17.2f|\n", current_user->balance);
                printf("==============================\n");
                printf("| 1. VIEW PROFILE            |\n");
                printf("| 2. VIEW STOCKS             |\n");
                printf("| 3. ADD NEW STOCK           |\n");
                printf("| 4. VIEW ALL USERS          |\n");
                printf("| 5. LOGOUT                  |\n");
                printf("==============================\n");
                printf("ENTER CHOICE: ");
                scanf("%d", &choice);
                
                switch(choice){
                    case 1:
                        printf("\n=============================\n");
                        printf("| ADMIN PROFILE             |\n");
                        printf("=============================\n");
                        printf("| Username: %-17s|\n", current_user->username);
                        printf("| Balance: $%-16.2f|\n", current_user->balance);
                        printf("| Role: ADMINISTRATOR       |\n");
                        printf("=============================\n");
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                        
                    case 2:
                        view_stocks();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                        
                    case 3:
                        add_new_stock();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                        
                    case 4:
                        view_all_users();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                        
                    case 5:
                        {
                            int confirm;
                            printf("\n==============================\n");
                            printf("| ARE YOU SURE YOU WANT TO   |\n");
                            printf("| LOGOUT?                    |\n");
                            printf("==============================\n");
                            printf("| 1. YES, LOGOUT             |\n");
                            printf("| 2. NO, STAY LOGGED IN      |\n");
                            printf("==============================\n");
                            printf("ENTER CHOICE: ");
                            scanf("%d", &confirm);
                            
                            if(confirm == 1){
                                save_data();
                                current_user->is_logged_in = false;
                                current_user = NULL;
                                printf("\n✓ LOGGED OUT SUCCESSFULLY!\n");
                            } else {
                                printf("\n✓ LOGOUT CANCELLED. STAYING LOGGED IN!\n");
                            }
                            printf("\nPress ENTER to continue...");
                            clear_input_buffer();
                            getchar();
                            break;
                        }
                        
                    default:
                        printf("\n✗ INVALID CHOICE!\n");
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                }
            } else {
                // REGULAR USER MENU
                printf("\n==============================\n");
                printf("| USER: %-21s|\n", current_user->username);
                printf("| BALANCE: $%-17.2f|\n", current_user->balance);
                printf("==============================\n");
                printf("| 1. VIEW PROFILE            |\n");
                printf("| 2. VIEW STOCKS             |\n");
                printf("| 3. BUY_STOCK               |\n");
                printf("| 4. VIEW PORFTFOLIO         |\n");
                printf("| 5. SELL STOCK              |\n");
                printf("| 6. ADD MONEY               |\n");
                printf("| 7. WITHDRAW MONEY          |\n");
                printf("| 8. VIEW TRANSACTION          |\n");
                printf("| 9. LOGOUT                  |\n");
                printf("==============================\n");
                printf("ENTER CHOICE: ");
                scanf("%d", &choice);
                
                switch(choice){
                    case 1:
                        printf("\n=============================\n");
                        printf("| PROFILE INFORMATION       |\n");
                        printf("=============================\n");
                        printf("| Username: %-17s|\n", current_user->username);
                        printf("| Balance: $%-16.2f|\n", current_user->balance);
                        printf("=============================\n");
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                        
                    case 2:
                        view_stocks();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;

                    case 3: 
                        buy_stock();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;

                    case 4: 
                        view_portfolio();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                        
                    case 5: 
                        sell_stock();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;

                    case 6: 
                        add_money();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;

                    case 7: 
                        withdraw_money();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;

                    case 8: 
                        view_transactions();
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;

                    case 9:
                        {
                            int confirm;
                            printf("\n==============================\n");
                            printf("| ARE YOU SURE YOU WANT TO   |\n");
                            printf("| LOGOUT?                    |\n");
                            printf("==============================\n");
                            printf("| 1. YES, LOGOUT             |\n");
                            printf("| 2. NO, STAY LOGGED IN      |\n");
                            printf("==============================\n");
                            printf("ENTER CHOICE: ");
                            scanf("%d", &confirm);
                            
                            if(confirm == 1){
                                save_data();
                                current_user->is_logged_in = false;
                                current_user = NULL;
                                printf("\n✓ LOGGED OUT SUCCESSFULLY!\n");
                            } else {
                                printf("\n✓ LOGOUT CANCELLED. STAYING LOGGED IN!\n");
                            }
                            printf("\nPress ENTER to continue...");
                            clear_input_buffer();
                            getchar();
                            break;
                        }
                        
                    default:
                        printf("\n✗ INVALID CHOICE!\n");
                        printf("\nPress ENTER to continue...");
                        clear_input_buffer();
                        getchar();
                        break;
                }
            }
        }
    }
    
    return 0;
}

void display_menu(){
    int choice;
    printf("\n=================================\n");
    printf("|  TRADING PLATFORM - MAIN MENU |\n");
    printf("=================================\n");
    printf("| 1. REGISTER USER              |\n");
    printf("| 2. LOGIN                      |\n");
    printf("| 3. EXIT                       |\n");
    printf("=================================\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d", &choice);

    switch (choice){
        case 1:
            register_user();
            break;
        case 2:
            login();
            break;
        case 3:
            save_data();
            printf("\nTHANK YOU! GOODBYE!\n\n");
            exit(0);
            break;
        default:
            printf("\n✗ INVALID CHOICE!\n");
    }
}

void register_user(){
    if(user_count >= MAX_USERS){
        printf("\n==============================\n");
        printf("| USER LIMIT REACHED, SORRY! |\n");
        printf("==============================\n");
        return;
    }
    
    char username[MAX_NAME], password[MAX_NAME];
    
    printf("\n==============================\n");
    printf("| USER REGISTRATION          |\n");
    printf("==============================\n");
    printf("| ENTER USERNAME: ");
    scanf("%s", username);
    
    for (int i = 0; i < user_count; i++){
        if(strcmp(users[i].username, username) == 0){
            printf("==============================\n");
            printf("| USER ALREADY EXISTS!       |\n");
            printf("==============================\n");
            return;
        }
    }
    
    printf("| ENTER PASSWORD: ");
    scanf("%s", password);
    
    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    users[user_count].balance = 10000.0;
    users[user_count].is_logged_in = false;
    users[user_count].is_admin = false;
    users[user_count].portfolio_count = 0;
    user_count++;
    
    printf("==============================\n");
    printf("| USER REGISTERED SUCCESSFULLY!|\n");
    printf("==============================\n");
}

void login(){
    char input_username[MAX_NAME], input_password[MAX_NAME];
    
    printf("\n==============================\n");
    printf("| USER LOGIN                 |\n");
    printf("==============================\n");
    printf("| ENTER USERNAME: ");
    scanf("%s", input_username);
    printf("| ENTER PASSWORD: ");
    scanf("%s", input_password);
    
    for (int i = 0; i < user_count; i++){
        if (strcmp(users[i].username, input_username) == 0){
            if (strcmp(users[i].password, input_password) == 0){
                current_user = &users[i];
                users[i].is_logged_in = true;
                printf("==============================\n");
                printf("| LOGIN SUCCESSFUL!          |\n");
                printf("==============================\n");
                printf("| WELCOME, %-18s|\n", input_username);
                printf("==============================\n");
                return;
            }
            else{
                printf("==============================\n");
                printf("| INVALID PASSWORD!          |\n");
                printf("==============================\n");
                return;
            }
        }
    }
    
    printf("==============================\n");
    printf("| USERNAME NOT FOUND!        |\n");
    printf("==============================\n");
}

void initialize_stocks(){
    strcpy(stocks[0].symbol, "AAPL");
    strcpy(stocks[0].company_name, "Apple Inc.");
    stocks[0].price = 175.50;

    strcpy(stocks[1].symbol, "GOOGL");
    strcpy(stocks[1].company_name, "Google Inc.");
    stocks[1].price = 190.50;

    strcpy(stocks[2].symbol, "MSFT");
    strcpy(stocks[2].company_name, "Microsoft Corp.");
    stocks[2].price = 175.50;

    strcpy(stocks[3].symbol, "OPENAI");
    strcpy(stocks[3].company_name, "OpenAI");
    stocks[3].price = 200.50;

    strcpy(stocks[4].symbol, "NVDA");
    strcpy(stocks[4].company_name, "NVIDIA Corp.");
    stocks[4].price = 134.50;

    strcpy(stocks[5].symbol, "ANTRP");
    strcpy(stocks[5].company_name, "Anthropic");
    stocks[5].price = 230.50;

    strcpy(stocks[6].symbol, "AMZN");
    strcpy(stocks[6].company_name, "Amazon Inc.");
    stocks[6].price = 100.50;

    strcpy(stocks[7].symbol, "TSLA");
    strcpy(stocks[7].company_name, "Tesla Inc.");
    stocks[7].price = 300.50;

    stock_count = 8;
    printf("\n✓ STOCK MARKET INITIALIZED WITH %d STOCKS!\n", stock_count);
}

void create_admin(){
    // Check if admin already exists
    for (int i = 0; i < user_count; i++){
        if (strcmp(users[i].username, "admin") == 0){
            return;
        }
    }
    
    // Create admin account
    strcpy(users[user_count].username, "admin");
    strcpy(users[user_count].password, "admin123");
    users[user_count].balance = 1000000.0;
    users[user_count].is_logged_in = false;
    users[user_count].is_admin = true;
    users[user_count].portfolio_count = 0;
    user_count++;
    
    printf("✓ Admin account created! (username: admin, password: admin123)\n");
}

void view_stocks(){
    printf("\n========================================\n");
    printf("|          STOCK MARKET                |\n");
    printf("========================================\n");
    printf("| Symbol  | Company Name        | Price     |\n");
    printf("|---------|---------------------|----------|\n");
    
    for (int i = 0; i < stock_count; i++){
        printf("| %-7s | %-19s | $%-8.2f |\n",
               stocks[i].symbol,
               stocks[i].company_name,
               stocks[i].price);
    }
    
    printf("========================================\n");
    printf("Total stocks available: %d\n", stock_count);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_new_stock(){ 
    if ( stock_count >= MAX_STOCKS){
        printf("|--STOCK LIMIT REACHED-----|\n");
        return;
    }
    printf("|----ADD NEW STOCK----|\n");
    char symbol[10],company_name[MAX_NAME];
    float price;
    printf("--ENTER STOCK SYMBOL----\n");
    scanf("%s",symbol);
    for (int i=0 ; i<stock_count;i++){
        if (strcmp(stocks[i].symbol,symbol)== 0){
            printf("|----STOCK ALREADY EXIST-----|\n");
            return;
        }
    }
    printf("|----ADD COMPANY NAME----|\n");
    clear_input_buffer();
    fgets(company_name,MAX_NAME,stdin);
    company_name[strcspn(company_name,"\n")] = 0;

    printf("|-----ENTER STOCK PRICE------| : $\n");
    scanf("%f",&price);
    if (price <= 0){
        printf("====================\n");
        printf("| INVALID PRICE    |\n");
        printf("====================\n");
        return;
    }
    strcpy(stocks[stock_count].symbol,symbol);
    strcpy(stocks[stock_count].company_name,company_name);
    stocks[stock_count].price = price;
    stock_count++;

    printf("===========================\n");
    printf("| STOCK ADDED SUCCESFULLY |\n");
    printf("===========================\n");
    printf("|SYMBOL %-18s|",symbol);
    printf("|NAME : %-21s|",company_name);
    printf("|PRICE : %-8.2f|",price);
}

void view_all_users() {
    printf("\n========================================\n");
    printf("|          ALL REGISTERED USERS        |\n");
    printf("========================================\n");
    
    if(user_count == 0) {
        printf("|  NO USERS REGISTERED YET!            |\n");
        printf("========================================\n");
        return;
    }
    
    printf("| No. | Username       | Balance    | Role  |\n");
    printf("|-----|----------------|------------|-------|\n");
    
    for (int i = 0; i < user_count; i++) {
        printf("| %-3d | %-14s | $%-9.2f | %-5s |\n",
               i+1,
               users[i].username,
               users[i].balance,
               users[i].is_admin ? "Admin" : "User");
    }
    
    printf("========================================\n");
    printf("Total users: %d\n", user_count);
}

Stock* find_stock_by_symbol(char *symbol) {
    for(int i = 0; i < stock_count; i++) {
        if(strcmp(stocks[i].symbol, symbol) == 0) {
            return &stocks[i];
        }
    }
    return NULL;
}

void buy_stock(){
    char symbol[10];
    int quantity;
    
    view_stocks();
    
    printf("\n--------BUY STOCK-------\n");
    printf("ENTER STOCK SYMBOL: ");
    scanf("%s", symbol);
    
    Stock *stock = find_stock_by_symbol(symbol);
    if(stock == NULL){
        printf("STOCK NOT FOUND\n");
        return;
    }
    
    printf("---ENTER QUANTITY-----: ");
    scanf("%d", &quantity);  
    
    if(quantity <= 0){
        printf("--INVALID QUANTITY--\n");
        return;
    }
    
    float total_cost = stock->price * quantity;
    
    printf("=================================\n");
    printf("|  ORDER SUMMARY                |\n");
    printf("=================================\n");
    printf("| STOCKS: %s (%s)\n", stock->company_name, stock->symbol);
    printf("| PRICE PER SHARE: $%.2f\n", stock->price);
    printf("| QUANTITY: %d\n", quantity);
    printf("| TOTAL COST: $%.2f\n", total_cost);
    printf("| YOUR BALANCE: $%.2f\n", current_user->balance);
    printf("=================================\n");
    
    if(total_cost > current_user->balance){
        printf("|---------INSUFFICIENT BALANCE-----------|\n");
        return;
    }
    
    int __choice;
    printf("CONFIRM PURCHASE (1 = YES) (0 = NO): ");
    scanf("%d", &__choice);
    
    if(__choice != 1){
        printf("|--------ORDER CANCELLED--------|\n");
        return;
    }
    
    current_user->balance -= total_cost;
    
    int found = -1;
    for(int i = 0; i < current_user->portfolio_count; i++){
        if(strcmp(current_user->portfolio[i].symbol, symbol) == 0){  
            found = i;
            break;  
        }
    }
    
    if(found != -1){
        PortfolioItem *item = &current_user->portfolio[found];
        float total_cost_old = item->avg_buy_price * item->quantity;
        float total_cost_new = stock->price * quantity;
        item->quantity += quantity;
        item->avg_buy_price = (total_cost_old + total_cost_new) / item->quantity;  
    } else {
        if(current_user->portfolio_count >= MAX_PORTFOLIO){
            printf("PORTFOLIO LIMIT REACHED\n");
            current_user->balance += total_cost;
            return;
        }
        strcpy(current_user->portfolio[current_user->portfolio_count].symbol, symbol);
        current_user->portfolio[current_user->portfolio_count].quantity = quantity;
        current_user->portfolio[current_user->portfolio_count].avg_buy_price = stock->price;
        current_user->portfolio_count++;
    }

    add_transaction("BUY", symbol, quantity, stock->price);
    
    printf("\n✓ PURCHASE SUCCESSFUL!\n");
    printf("New balance: $%.2f\n", current_user->balance);
}

void view_portfolio(){
     printf("\n========================================\n");
    printf("|          MY PORTFOLIO                |\n");
    printf("========================================\n");
    printf("| Balance: $%-29.2f|\n", current_user->balance);
    printf("========================================\n");
    
    if(current_user->portfolio_count == 0) {
        printf("|  NO STOCKS IN PORTFOLIO YET!         |\n");
        printf("========================================\n");
        return;
    }
    
    printf("| Symbol | Qty  | Avg Price | Current  | Value    | P/L      |\n");
    printf("|--------|------|-----------|----------|----------|----------|\n");
     float total_investment = 0;
     float total_current_value = 0;
     for ( int i = 0; i < current_user->portfolio_count;i++){
        Stock *stock = find_stock_by_symbol(current_user->portfolio[i].symbol);
     
     if (stock != NULL) {
        
            float investment = current_user->portfolio[i].avg_buy_price * current_user->portfolio[i].quantity;
            float current_value = stock->price * current_user->portfolio[i].quantity;
            float profit_loss = current_value - investment;
            
            printf("| %-6s | %-4d | $%-8.2f | $%-7.2f | $%-7.2f | %c$%-6.2f|\n",
                   current_user->portfolio[i].symbol,
                   current_user->portfolio[i].quantity,
                   current_user->portfolio[i].avg_buy_price,
                   stock->price,
                   current_value,
                   profit_loss >= 0 ? '+' : '-',
                   profit_loss >= 0 ? profit_loss : -profit_loss);
            
            total_investment += investment;
            total_current_value += current_value;
     }
}
float total_pl = total_current_value - total_investment;
printf("=================================\n");
printf("| TOTAL INVESTMENT : %18.2f\n",total_investment);
printf("| CURRENT VALUE : %21.2f\n",total_current_value);
printf("| Total P/L: %c$%-24.2f|\n", 
           total_pl >= 0 ? '+' : '-',
           total_pl >= 0 ? total_pl : -total_pl);
printf("PORTFOLIO + CASH : %8.2f\n",current_user->balance + total_current_value);             
}

void sell_stock(){
    if(current_user->portfolio_count == 0){
        printf("YOU DONT OWN ANY STOCK :)\n");
        return;
    }
    
    view_portfolio();  
    
    char symbol[10];
    int quantity;
    
    printf("|---ENTER SYMBOL YOU WANT TO SELL: ");
    scanf("%s", symbol);
    
    int found = -1;
    for(int i = 0; i < current_user->portfolio_count; i++){
        if(strcmp(current_user->portfolio[i].symbol, symbol) == 0) {  
            found = i;
            break;
        }
    }
    
    if(found == -1){
        printf("YOU DONT OWN THIS STOCK :)\n");
        return;
    }
    
    PortfolioItem *item = &current_user->portfolio[found];
    Stock *stock = find_stock_by_symbol(symbol);  
    
    printf("YOU OWN %d shares\n", item->quantity);
    printf("ENTER QUANTITY TO SELL: ");
    scanf("%d", &quantity);
    
    if(quantity <= 0 || quantity > item->quantity){
        printf("INVALID QUANTITY\n");
        return;
    }
    
    float total_value = stock->price * quantity;  
    float profit_loss = (stock->price - item->avg_buy_price) * quantity;  
    
    printf("===========================\n");
    printf("|   ORDER SUMMARY         |\n");
    printf("===========================\n");
    printf("| STOCK: %s\n", stock->company_name);
    printf("| SELLING %d SHARES\n", quantity);
    printf("| TOTAL VALUE: $%.2f\n", total_value);
    printf("| PROFIT/LOSS: %c$%.2f\n",  
            profit_loss >= 0 ? '+' : '-',  
           profit_loss >= 0 ? profit_loss : -profit_loss);  
    printf("===========================\n");
    
    int confirm;
    printf("CONFIRM SELL: (1=YES) (0=NO): ");
    scanf("%d", &confirm);
    
    if(confirm != 1){
        printf("SELLING CANCELLED\n");
        return;
    }
    
    current_user->balance += total_value;
    item->quantity -= quantity;
    
    if(item->quantity == 0){  
        for(int i = found; i < current_user->portfolio_count - 1; i++){
            current_user->portfolio[i] = current_user->portfolio[i + 1];
        }
        current_user->portfolio_count--;
    }
    
    add_transaction("SELL", symbol, quantity, stock->price);

    printf("\n✓ SALE SUCCESSFUL!\n");
    printf("Received: $%.2f\n", total_value);
    printf("New balance: $%.2f\n", current_user->balance);
}

void add_money (){
    float amount;
    printf("|----ENTER AMONUT----|:\n");
    scanf("%f",&amount);
    if (amount <= 0){
        printf("|----INVALID AMOUNT----|\n");
        return;
    }
    current_user->balance += amount;
    printf("======================================\n");
    printf("|----AMOUNT ADDED SUCCESFULLY--------|\n");
    printf("======================================\n");
    printf("| AMOUNT ADDED : %-18.2f|\n",amount);
    printf("| BALANCE : %-18.2f|\n",current_user->balance);
    printf("====================================\n");
    return;
}

void withdraw_money(){
    float amount;
    printf("|----ENTER AMOUNT----|:\n");
    scanf("%f",&amount);
     if (amount <= 0){
        printf("|----INVALID AMOUNT-----|\n");
        return;
     }
     current_user->balance -= amount;
      printf("======================================\n");
    printf("|-------- WITHDRAWN SUCCESFULLY--------|\n");
    printf("=======================================\n");
    printf("| AMOUNT WITHDRAWN : %-18.2f|\n",amount);
    printf("| BALANCE : %-18.2f|\n",current_user->balance);
    printf("=======================================\n");
    return;

}

void add_transaction(char *type, char *symbol, int quantity, float price){
    if (transaction_count >= MAX_TRANSACTIONS){
        printf("\nTRANSACTION LIMIT REACHED :) \n ");
        return;
    }
    transactions[transaction_count].id = transaction_count + 1;
    strcpy(transactions[transaction_count].username,current_user->username);
    strcpy(transactions[transaction_count].symbol,symbol);
    strcpy(transactions[transaction_count].type,type);
    strcpy(transactions[transaction_count].date,"04/04/2026");
    transactions[transaction_count].quantity = quantity;
    transactions[transaction_count].price = price;
    transactions[transaction_count].total = price * quantity;
    transaction_count++;
}

void view_transactions() {
    printf("\n--- TRANSACTION HISTORY ---\n");
    if(transaction_count == 0) {
        printf("No transactions yet.\n");
        return;
    }
    
    for(int i = transaction_count - 1; i >= 0; i--) {
        if(strcmp(transactions[i].username, current_user->username) == 0) {
            printf("%d | %s | %s | %d shares @ $%.2f | Total: $%.2f\n",
                   transactions[i].id,
                   transactions[i].type,
                   transactions[i].symbol,
                   transactions[i].quantity,
                   transactions[i].price,
                   transactions[i].total);
        }
    }
}

void save_data() {
    FILE *f = fopen("trading_data.dat", "w");
    if(!f) return;
    
    
    fprintf(f, "%d\n", user_count);
    for(int i = 0; i < user_count; i++) {
        fprintf(f, "%s %s %.2f %d %d\n",
                users[i].username,
                users[i].password,
                users[i].balance,
                users[i].is_admin,
                users[i].portfolio_count);
        
        
        for(int j = 0; j < users[i].portfolio_count; j++) {
            fprintf(f, "%s %d %.2f\n",
                    users[i].portfolio[j].symbol,
                    users[i].portfolio[j].quantity,
                    users[i].portfolio[j].avg_buy_price);
        }
    }
    
    
    fprintf(f, "%d\n", stock_count);
    for(int i = 0; i < stock_count; i++) {
        fprintf(f, "%s %s %.2f\n",
                stocks[i].symbol,
                stocks[i].company_name,
                stocks[i].price);
    }
    
    
    fprintf(f, "%d\n", transaction_count);
    for(int i = 0; i < transaction_count; i++) {
        fprintf(f, "%d %s %s %s %d %.2f %.2f %s\n",
                transactions[i].id,
                transactions[i].username,
                transactions[i].symbol,
                transactions[i].type,
                transactions[i].quantity,
                transactions[i].price,
                transactions[i].total,
                transactions[i].date);
    }
    
    fclose(f);
    printf("Data saved!\n");
}

void load_data() {
    FILE *f = fopen("trading_data.dat", "r");
    if(!f) return;  
    
    
    fscanf(f, "%d", &user_count);
    for(int i = 0; i < user_count; i++) {
        fscanf(f, "%s %s %f %d %d",
               users[i].username,
               users[i].password,
               &users[i].balance,
               (int*)&users[i].is_admin,
               &users[i].portfolio_count);
        users[i].is_logged_in = false;
        
        
        for(int j = 0; j < users[i].portfolio_count; j++) {
            fscanf(f, "%s %d %f",
                   users[i].portfolio[j].symbol,
                   &users[i].portfolio[j].quantity,
                   &users[i].portfolio[j].avg_buy_price);
        }
    }
    
    
    fscanf(f, "%d", &stock_count);
    for(int i = 0; i < stock_count; i++) {
        fscanf(f, "%s %s %f",
               stocks[i].symbol,
               stocks[i].company_name,
               &stocks[i].price);
    }
    
    
    fscanf(f, "%d", &transaction_count);
    for(int i = 0; i < transaction_count; i++) {
        fscanf(f, "%d %s %s %s %d %f %f %s",
               &transactions[i].id,
               transactions[i].username,
               transactions[i].symbol,
               transactions[i].type,
               &transactions[i].quantity,
               &transactions[i].price,
               &transactions[i].total,
               transactions[i].date);
    }
    
    fclose(f);
    printf("Data loaded!\n");
}
