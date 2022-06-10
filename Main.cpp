// Libraries used
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <unordered_map>
using namespace std;
// Oders class to store order information for each Customer
class Order
{
    private:
    //variables
        string seats;
        int adult_seat, child_seat, senior_seat, auditorium;
    public:
    //constructor
        Order() {};
        Order(string seat, int audi, int adult, int child, int senior) {
            seats = seat;
            auditorium = audi;
            adult_seat = adult;
            child_seat = child;
            senior_seat = senior;
        }
    //mutators
        void setAdult(int num) { adult_seat = num; }
        void setChild(int num) { child_seat = num; }
        void setSenior(int num) { senior_seat = num; }
        //When seats are added or removed, arranges then alphabetically and stores
        void setSeats(string seat) {seats=seat;
            seats+=", ";
            int max=int(seats.length()/4);
            // creates and stores seat in array
            string *arr=new string[int(seats.length()/4)];
            for(int i=0;i<max;i++){
                arr[i]=seats.substr(0,2);
                seats=seats.substr(4,seats.length());
            }
            string key;int j;
            //sorts them by row number and seat letter
            for(int i = 1; i<max; i++) {
              key = arr[i];
              j = i;
              while(j > 0 && arr[j-1]>key) {
                 arr[j] = arr[j-1];
                 j--;
              }
              arr[j] = key;
            }
            // stores seats in the string
            seats="";
            for(int i=0;i<max;i++){
                seats+= arr[i] + ", ";
            }
            seats=seats.substr(0,seats.length()-2);
        }
        void setAud(int a) {auditorium = a; }
    //accessors
        string getSeats() {return seats;}
        int getAud() {return auditorium; }
        int getTotTicket() { return (adult_seat + child_seat + senior_seat); }
        int getAdult() { return adult_seat; }
        int getChild() { return child_seat; }
        int getSenior() { return senior_seat; }
};
// Customer class to store Customer data(username, password, and orders)
class Customer
{
    private:
    //variables
        string username, password;
        vector<Order> orders;
        int numOrders;
    public:
    //constuctors
        Customer() {};
        Customer(string user, string pass) {
            username = user;
            password = pass;
            numOrders = 0;
        }
    //accessors
        string getUsername(){ return username; }
        string getPassword(){ return password; }
        int getNumOrders(){ return numOrders; }
        vector<Order> getOrders(){ return orders; }
    //mutators
        void setNumOrder(int num){numOrders=num;}
        void setOrder(vector<Order> o){
            orders=o;
        }
        void addOrder(Order add){
            orders.push_back(add);
            numOrders++;
        }
        void repOrder(Order add, int index){
            //deletes orders if empty
            orders.erase(orders.begin()+index);
            if (add.getSeats()!="")
                orders.insert(orders.begin()+index,add);
            else
                numOrders--;
        }
        void cancelOrder(int index){
            orders.erase(orders.begin()+index);
            numOrders--;
        }
        // Prints order information for Customer
        void printOrder(){
            if (numOrders<1) {
                cout << "No orders\n";
            }
            else{
                for (int j=0; j<numOrders; j++) {
                    Order o = orders.at(j);
                    cout <<"Auditorium " <<o.getAud() <<", " <<o.getSeats() <<"\n" <<o.getAdult() << " adult, " <<o.getChild() << " child, " <<o.getSenior() << " senior\n";
                }
            }
            cout << endl;
        }
        // Prints order information for Customer to choose and update
        Order updateOrder(int &index){
            if (numOrders<1) {
                cout << "No orders\n";
            }
            else{
                for (int j=0; j<numOrders; j++) {
                    Order o = orders.at(j);
                    cout <<"Order " <<j+1<<endl;
                    cout <<"Auditorium " <<o.getAud() <<", " <<o.getSeats() <<"\n";
                }
            }
            cout << endl;
            // asks user to choose from orders available and validates
            int achoice=0;
            while (achoice<=0 || achoice>numOrders){
                cout << "Choose order:\t";
                while (!(cin >> achoice)){
                    cout << "ERROR: a number must be entered: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
            }
            Order o = orders.at(achoice-1);
            // returns order and access to index
            index=achoice-1;
            return o;
        }
        // Prints order information and sums up order total for Customer
        void printReceipt(){
            double orderTot=0, cusTot=0;
            // if Customer has no orders
            if (numOrders<1) {
                cout << "No orders\n" << "Order Total: $" << fixed << setprecision(2) << orderTot << endl << endl;
                cout << "Customer Total: $0.00\n\n";
            }
            // if Customer has orders then displays rder information, order total, and finally customer total
            else{
                for (int j=0; j<numOrders; j++) {
                    Order o = orders.at(j);
                    cout <<"Auditorium " <<o.getAud() <<", " <<o.getSeats() <<"\n" <<o.getAdult() << " adult, " <<o.getChild() << " child, " <<o.getSenior() << " senior\n";
                    orderTot= (o.getAdult()*10)+(o.getSenior()*7.5)+(o.getChild()*5);
                    cusTot+=orderTot;
                    cout << "Order Total: $" << fixed << setprecision(2) << orderTot << endl << endl;
                }
                cout << "Customer Total: $" << fixed << setprecision(2) << cusTot << endl << endl;
            }
        }
};

// Takes input file to create and return auditorium
char** setAud(string file, int &row, int &col){
    // Variables to store and access temporarily
    ifstream infile;
    string s[10]; char c[26];
    row=0;col=0;
    infile.open(file);
    // Counts row, column, and sotres each line
    if (infile.good()){
        while (getline(infile,s[row])){
            row++;
        }
    }
    col=(int)s[0].length();
    // Creates Auditorium array and stores each seat as char
    char **Audi = new char*[row];
    for (int j=0;j<row;j++){
        Audi[j] = new char[col];
        strcpy(c, s[j].c_str());
        for (int k=0;k<col;k++){
            Audi[j][k]=(c[k]);
        }
    }
    infile.close();
    // Returns auditorium
    return Audi;
}
// Prints auditorium for user by rows and columns to reserve
void printAud(char **Audi, int row, int col){
    string ss = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    cout << "\n  " << ss.substr(0, col)<<" \n";
    // Prints '#' if reserved '.' if open by rows and columns
    for (int j=0;j<row;j++){
        cout << j+1 <<" ";
        for (int k=0;k<col;k++){
            if(Audi[j][k]!='.')
            cout << '#';
            else
            cout << Audi[j][k];
        }
        cout << endl;
    }
}
// Funtion to check if the string revieved is empty(returns true) or reserved(returns false)
bool check (string a,int tot){
    for ( int j = 0; j < tot; j++){
            if (a[j]!='.')
                return false;
        }
    return true;
}
// Funtion to Calculates distance between 2 points
double calcDistance(double x1, double x2, double y1, double y2){
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
string reserve(char **Audi, int row, int col, int &adult, int &child, int &senior){
    // Displays Auditorium for user to choose from
    printAud(Audi,row,col);
    // variables to get valid user input and reserve tickets
    int rn=0, cn=0, at=0, ct=0, st=0, tt=0, j=0;
    char sl;
    bool alp = true;
    bool ro=false,co=false,AD=false,CD=false,SD=false;
    char alpha[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // asks and checks user for vaild row number
    while(!ro){
        cout << "\nEnter row number:               ";
        while (!(cin >> rn)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (rn<=row&&rn>0)
            ro=true;
        else
        cout << "Invalid";
    }
    // asks user for vaild seat letter
    while(!co){
        sl=' ';
        cout <<"Enter starting seat letter:     ";
        cin >> sl;
        j=0;
        cn=0;
    // converts seat letter into number for the 2D array and checks if the user input of seat letter is valid column number
        while (alp){
            if (alpha[j]==sl){
                cn=j;
                alp=false;
            }
            j++;
        }
        if (cn<=col && cn>=0)
            co=true;
        else{
            cout << "Invalid\n";
            alp=true;
        }
    }
    // asks and checks user for vaild number of adult tickets
    while(!AD){
        cout << "Enter number of adult tickets:  ";
        while (!(cin >> at)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (at>-1)
            AD=true;
        else
            cout << "Invalid\n";
    }
    // asks and checks user for vaild number of child tickets
    while(!CD){
        cout << "Enter number of child tickets:  ";
        while (!(cin >> ct)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (ct>-1)
            CD=true;
        else
            cout << "Invalid\n";
    }
    // asks and checks user for vaild number of senior tickets
    while(!SD){
        cout << "Enter number of senior tickets: ";
        while (!(cin >> st)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (st>-1)
            SD=true;
        else
            cout << "Invalid\n";
    }
    // total number of tickets user wants in a row
    tt = at+ct+st;
    adult=at;child=ct;senior=st;
    // loop to at the user's wanted seats
    string comp;
    for (j=0;j<tt;j++){
        comp+= Audi[rn-1][cn+j];
    }
    // calls function to check if the seats are available
    bool avai;
    avai= check(comp,tt);
    string ret="";
    // if seats are available, loop will reserve seats by A for adult, C for child, and S for senior in order
    if (avai){
        for (j=0;j<tt;j++){
            if (at>0){
                Audi[rn-1][cn+j]='A';
                at--;
            }
            else if (ct>0){
                Audi[rn-1][cn+j]='C';
                ct--;
            }
            else if (st>0){
                Audi[rn-1][cn+j]='S';
                st--;
            }
        }
        // Stores reserved seats(row and column)
        stringstream ss;
        ss << rn;
        string str = ss.str();
        for(j=0;j<tt;j++)
            ret+= str + char(65+cn+j) + ", ";
        ret = ret.substr(0,ret.length()-2);
        cout << "seats are available and reserved!\n\n";
    }
    // if requested seats are not available then searches for best available
    else{
        // variable for calculating best seats in auditorium
        int i=0; j=0;
        int coord[] = {-1, -1};
        double centerx = (col + 1) / 2.0;
        double centery = (row + 1) / 2.0;
        double centerSeat = (tt+ 1) / 2.0;
        double shortDis = calcDistance(0, centerx, 0, centery);
        double distance = 0;
        // checks each seat for availability and choose the closest seat to middle of auditorium
        while(i < row){
            while(j + tt - 1 < col){
                // checks if total seats are available continuously
                comp="";
                for (int k=0;k<tt;k++){
                    comp+= Audi[i][j+k];
                }
                avai= check(comp,tt);
                // if seats are available, then checks if its the closest distance to the middle of auditorium
                if(avai){
                    distance = calcDistance(j + centerSeat , centerx, i + 1 ,centery);
                    // stores the seat if its the closest
                    if(distance < shortDis) {
                        shortDis = distance;
                        coord[0] = i + 1;
                        coord[1] = j + 1;
                    }
                    // if tie, then chooses row closest to the middle of the auditorium
                    if(distance == shortDis) {
                        if(abs(coord[0] - centery) > abs((i + 1) - centery)) {
                            shortDis = distance;
                            coord[0] = i + 1;
                            coord[1] = j + 1;
                        }
                        // if tie for closest row, then chooses with the smaller number
                        else if ((abs(coord[0] - centery) == abs((i + 1) - centery))) {
                            if(i + 1 < coord[0]) {
                                shortDis = distance;
                                coord[0] = i + 1;
                                coord[1] = j + 1;
                            }
                        }
                    }
                }
                j++;
            }
            j = 0;
            i++;
        }
        // if no best seats are found
        if(coord[0] < 0 && coord[1] < 0)
            cout << "no seats avaliable\n";
        // if best seats found, then asks user to reserve them
        else {
            cout << "Found best seats at row " << coord[0] << (char)(coord[1] + 64) << "-" << coord[0] <<
            (char)(coord[1] + 63 + tt) <<endl;
            cout << "Would you like to reserve this seat? (Y/N) ";
            cin >> sl;
            //if user chooses to reserve best, loop will reserve seats by A for adult, C for child, and S for senior in order
            if(sl == 'Y' || sl == 'y') {
                for (j=0;j<tt;j++) {
                    if (at>0) {
                        Audi[coord[0]-1][coord[1]+j-1]='A';
                        at--;
                    }
                    else if (ct>0) {
                        Audi[coord[0]-1][coord[1]+j-1]='C';
                        ct--;
                    }
                    else if (st>0) {
                        Audi[coord[0]-1][coord[1]+j-1]='S';
                        st--;
                    }
                }
                // Stores reserved seats(row and column)
                stringstream ss;
                ss << coord[0];
                string str = ss.str();
                for(j=0;j<tt;j++)
                    ret+= str + (char)(coord[1] + 64 +j) + ", ";
                ret = ret.substr(0,ret.length()-2);
                cout << "Seats are reserved!\n\n";
            }
        }
    }
    // Returns reserved seats
    return ret;
}
//
string addSeats(char **Audi, int row, int col, int &adult, int &child, int &senior){
    // Displays Auditorium for user to choose from
    printAud(Audi,row,col);
    // variables to get valid user input and reserve tickets
    int rn=0, cn=0, at=0, ct=0, st=0, tt=0, j=0;
    char sl;
    bool alp = true;
    bool ro=false,co=false,AD=false,CD=false,SD=false;
    char alpha[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // asks and checks user for vaild row number
    while(!ro){
        cout << "\nEnter row number:               ";
        while (!(cin >> rn)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (rn<=row&&rn>0)
            ro=true;
        else
        cout << "Invalid";
    }
    // asks user for vaild seat letter
    while(!co){
        sl=' ';
        cout <<"Enter starting seat letter:     ";
        cin >> sl;
        j=0;
        cn=0;
    // converts seat letter into number for the 2D array and checks if the user input of seat letter is valid column number
        while (alp){
            if (alpha[j]==sl){
                cn=j;
                alp=false;
            }
            j++;
        }
        if (cn<=col && cn>=0)
            co=true;
        else{
            cout << "Invalid\n";
            alp=true;
        }
    }
    // asks and checks user for vaild number of adult tickets
    while(!AD){
        cout << "Enter number of adult tickets:  ";
        while (!(cin >> at)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (at>-1)
            AD=true;
        else
            cout << "Invalid\n";
    }
    // asks and checks user for vaild number of child tickets
    while(!CD){
        cout << "Enter number of child tickets:  ";
        while (!(cin >> ct)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (ct>-1)
            CD=true;
        else
            cout << "Invalid\n";
    }
    // asks and checks user for vaild number of senior tickets
    while(!SD){
        cout << "Enter number of senior tickets: ";
        while (!(cin >> st)){
            cout << "ERROR: a number must be entered: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        if (st>-1)
            SD=true;
        else
            cout << "Invalid\n";
    }
    // total number of tickets user wants in a row
    tt = at+ct+st;
    adult=at;child=ct;senior=st;
    // loop to at the user's wanted seats
    string comp;
    for (j=0;j<tt;j++){
        comp+= Audi[rn-1][cn+j];
    }
    // calls function to check if the seats are available
    bool avai;
    avai= check(comp,tt);
    string ret="";
    // if seats are available, loop will reserve seats by A for adult, C for child, and S for senior in order
    if (avai){
        for (j=0;j<tt;j++){
            if (at>0){
                Audi[rn-1][cn+j]='A';
                at--;
            }
            else if (ct>0){
                Audi[rn-1][cn+j]='C';
                ct--;
            }
            else if (st>0){
                Audi[rn-1][cn+j]='S';
                st--;
            }
        }
        // Stores reserved seats(row and column)
        stringstream ss;
        ss << rn;
        string str = ss.str();
        for(j=0;j<tt;j++)
            ret+= str + char(65+cn+j) + ", ";
        ret = ret.substr(0,ret.length()-2);
        cout << "seats are available and reserved!\n\n";
    }
    else
        cout << "seats are not available\n\n";
    return ret;
}
// Takes in auditorium, seat, and updates seat type to delete seat from order
string deleteSeat(char **Audi, string seat, char &type){
    string rem="",tem="";
    int rn=-1,cn=-1;
    // Asks user for a valid row number
    cout << "Enter row number:\t";
    while (!(cin >> rn)){
        cout << "ERROR: a number must be entered: ";
        cin.clear();
        cin.ignore(123, '\n');
    }
    stringstream ss;
    ss << rn;
    rem= ss.str();
    // Asks user for a valid seat letter
    while(!(tem.length()==1)){
        cout << "Enter seat letter:\t";
        cin >> tem;
    }
    // Converts seat letter to column number
    bool alp=true;int j=0;
    string alpha= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    while (alp){
        if (alpha[j]==tem[0]){
            cn=j;
            alp=false;
        }
        j++;
    }
    rem+=tem;
    rem+=", ";
    bool f=false;
    int i=-1;
    // finds if the seat to delete is in the order
    if (seat.find(rem) != std::string::npos) {
        f=true;
        i = int(seat.find(rem));
        // updates seat type and unreserves seat
        type=Audi[rn-1][cn];
        Audi[rn-1][cn]='.';
        if (i != -1)
            seat.erase(i, rem.length());
    }
    // finds if the seat to delete is the last seat in the order
    else{
        rem=rem.substr(0,rem.find(", "));
        if (seat.find(rem) != std::string::npos) {
            f=true;
            i = int(seat.find(rem));
            // updates seat type and unreserves seat
            type=Audi[rn-1][cn];
            Audi[rn-1][cn]='.';
            if (i != -1)
                seat.erase(i, rem.length());
            if (seat.length()>1)
                seat.erase(seat.length()-2, 2);
        }
    }
    // If seat requested to delete was not in the order then recursive calls again
    if (!f){
        cout << "Not found. Try Again\n";
        seat= deleteSeat(Audi, seat, type);
    }
    return seat;
}
// Takes in auditoriuma and seat to delete order
void cancelSeats(char **Audi, string seats){
    seats+=", ";
    string temp="";
    // loop to remove every seat from order
    for(int i=0;i<int(seats.length()+2);i++){
        // parses seats to be removed one by one
        if(seats.length()>0){
            temp=seats.substr(0,seats.find(","));
            seats=seats.substr(seats.find(",")+2);
            char sl=temp[temp.length()-1];
            temp=temp.substr(0,temp.length()-1);
            // gets row number
            int rn=stoi(temp),cn=0,j=0;
            bool alp=true;
            // converts seat letter to column number
            char alpha[]= "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            while (alp){
                if (alpha[j]==sl){
                    cn=j;
                    alp=false;
                }
                j++;
            }
            // unreserves seat
            Audi[rn-1][cn]='.';
        }
    }
}
// Takes in Auditorium and writes auditorium to output file
void printAudi(char **Audi, int row, int col, string file){
    // Opens output file
    ofstream myfile;
    myfile.open(file);
    // Loop for each row
    for (int j=0;j<row;j++){
        // Loop for each seat in row
        for (int k=0;k<col;k++){
            // Writes data to output file
            myfile << Audi[j][k];
        }
        myfile << endl;
    }
    myfile.close();
}
// Takes in Auditorium and updates data variables
void report(char **Audi,int row,int col,int &open,int &reserved,int &adult,int &child,int &senior,double &sale){
    // Loop for each row
    for (int j=0;j<row;j++){
        // Loop for each seat in row
        for (int k=0;k<col;k++){
            // Updates data by seat type
            switch (Audi[j][k]){
                case 'A':
                    adult ++; reserved ++; sale+=10.00;
                    break;
                case 'C':
                    child ++; reserved ++; sale+=5.00;
                    break;
                case 'S':
                    senior ++; reserved ++; sale+=7.50;
                    break;
                case '.':
                    open++;
                    break;
                default:
                    break;
            }
        }
    }
}
/*-----------------------------------------------------------------MAIN-----------------------------------------------------------------*/
int main(){
    // Initialize, open file, and store auditorium in array
    char **A1;
    int a1row=0, a1col=0;
    A1 = setAud("A1.txt",a1row,a1col);
    char **A2;
    int a2row=0, a2col=0;
    A2 = setAud("A2.txt",a2row,a2col);
    char **A3;
    int a3row=0, a3col=0;
    A3 = setAud("A3.txt",a3row,a3col);
    // Variable to store and run the menu
    bool admin=false, login=false, end=false;
    string username=" ", password, temp;
    int choice=0, achoice=0, totusers=0, totOrders=0;
    vector<Order> orders;
    // Initialize customers and unordermap by key and customer
    unordered_map<string, Customer> map;
    Customer *a = new Customer();
    // Opens file with usernames and passwords to store in unorderedmp
    ifstream infile;
    infile.open("userdb.dat");
    if (infile.good()){
        while (getline(infile,temp)){
            // seperates username and password to store
            username=temp.substr(0,temp.find(' '));
            password=temp.substr(temp.find(" ")+1);
            a = new Customer(username,password);
            // stores user to map
            map[username] = *a;
            totusers++;
        }
    }
    // Program runs until the admin exits
    while (!end){
        // If not logged in, then asks for valid username and password
        if(!login){
            admin=false;
            choice = 0;
            cout << "Username: \t";
            cin >> username;
            // Finds username in the map, if not found, then user trys again for valid username
            if (map.end()==map.find(username))
                cout << "Username not found\t Try again\n";
            else{
                // Finds username in the map(by hashing) and stores customer data temporarily
                unordered_map<string, Customer>:: iterator itr= map.find(username);
                Customer log = (itr->second);
                // Asks user for valid password, user has 3 tries or else starts from beginning
                password="";
                while (log.getPassword()!=password && choice<3){
                    cout << "Password: \t";
                    cin >> password;
                    // If incorrest password, then try again for 3 tries
                    if (log.getPassword()!=password) {
                        cout << "Invalid password\n";
                        choice++;
                    }
                }
                // If user got password within 3 tries, then user logs in
                if (choice<3) {
                    login=true;
                    admin=false;
                    // Checks if the user is the admin
                    if (username.compare("admin") == 0)
                        admin=true;
                    // Stores users data from temporarily
                    totOrders=log.getNumOrders();
                    orders=log.getOrders();
                    a=new Customer(username,password);
                    a->setNumOrder(totOrders);
                    a->setOrder(orders);
                }
            }
        }
        // If logged in by admin
        if (admin){
            // Prints admin menu
            cout <<"1. Print Report\n2. Logout\n3. Exit\n";
            choice=0;
            // Asks for valid input
            while (choice<=0 || choice>3){
                while (!(cin >> choice)){
                    cout << "ERROR: a number must be entered: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
            }
            // If admin chooses to print report
            if (choice==1){
                // variables to store auditorium and total data
                int open=0, reserved=0, adult=0, child=0, senior=0; double sale=0;
                int Topen=0, Treserved=0, Tadult=0, Tchild=0, Tsenior=0; double Tsale=0;
                // calls report function and recieves auditorium 1 information
                report(A1, a1row, a1col, open, reserved, adult, child, senior, sale);
                // updates total data
                Topen+=open; Treserved+=reserved; Tadult+=adult; Tchild+=child; Tsenior+=senior; Tsale+=sale;
                // prints Auditorium 1 information
                cout << "Auditorium 1\t" << open <<"\t"<< reserved <<"\t"<< adult <<"\t"<< child <<"\t"<< senior <<"\t$"<< fixed << setprecision(2) << sale << endl;
                // resets
                open=0; reserved=0; adult=0; child=0; senior=0; sale=0;
                // calls report function and recieves auditorium 2 information
                report(A2, a2row, a2col, open, reserved, adult, child, senior, sale);
                // updates total data
                Topen+=open; Treserved+=reserved; Tadult+=adult; Tchild+=child; Tsenior+=senior; Tsale+=sale;
                // prints Auditorium 2 information
                cout << "Auditorium 2\t" << open <<"\t"<< reserved <<"\t"<< adult <<"\t"<< child <<"\t"<< senior <<"\t$"<< fixed << setprecision(2) << sale << endl;
                // resets
                open=0; reserved=0; adult=0; child=0; senior=0; sale=0;
                // calls report function and recieves auditorium 3 information
                report(A3, a3row, a3col, open, reserved, adult, child, senior, sale);
                // updates total data
                Topen+=open; Treserved+=reserved; Tadult+=adult; Tchild+=child; Tsenior+=senior; Tsale+=sale;
                // prints Auditorium 3 information
                cout << "Auditorium 3\t" << open <<"\t"<< reserved <<"\t"<< adult <<"\t"<< child <<"\t"<< senior <<"\t$"<< fixed << setprecision(2) << sale << endl;
                // prints total added up information of all 3 Auditoriums
                cout << "Total       \t" << Topen <<"\t"<< Treserved <<"\t"<< Tadult <<"\t"<< Tchild <<"\t"<< Tsenior <<"\t$"<< fixed << setprecision(2) << Tsale << endl;
            }
            // If admin chooses to log out, then go back to beginning
            else if (choice==2)
                login= false;
            // If admin chooses to quit, then end program
            else if (choice==3)
                end=true;
        }
        // If logged in by customer
        else if (login){
            // Asks user for action to be performed
            cout <<"1. Reserve Seats\n2. View Orders\n3. Update Orders\n4. Display Reciept\n5. Log Out\n";
            choice=0;
            // validates user input for choice
            while (choice<=0 || choice>5){
                while (!(cin >> choice)){
                    cout << "ERROR: a number must be entered: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
            }
            // If user chooses to Reserve seats
            if (choice==1){
                // Asks user to pick one of three auditoriums
                cout << "1. Auditorium 1 \n2. Auditorium 2 \n3. Auditorium 3\n";
                achoice=0;
                int at=0,ct=0,st=0;
                string seats="";
                // validates user input for auditorium
                while (achoice<=0 || achoice>3){
                    cout << "Enter Auditorium:\t";
                    while (!(cin >> achoice)){
                        cout << "ERROR: a number must be entered: ";
                        cin.clear();
                        cin.ignore(123, '\n');
                    }
                    // If user chooses auditorium 1, then pass in auditorium 1 and its details to reserve function
                    if (achoice==1) {
                        seats=reserve(A1,a1row,a1col,at,ct,st);
                    }
                    // If user chooses auditorium 2, then pass in auditorium 2 and its details to reserve function
                    else if (achoice==2) {
                        seats=reserve(A2,a2row,a2col,at,ct,st);
                    }
                    // If user chooses auditorium 3, then pass in auditorium 3 and its details to reserve function
                    else if (achoice==3) {
                        seats=reserve(A3,a3row,a3col,at,ct,st);
                    }
                    // If seats were reserved
                    if(seats!=""){
                        // create new order and add it to customer data
                        Order* o = new Order(seats, achoice, at, ct, st);
                        a->addOrder(*o);
                    }
                }
            }
            // If user chooses to View Orders, then customer's printOrder function is called
            else if (choice==2)
                a->printOrder();
            // If user chooses to Update Order
            else if (choice==3){
                // if user has more than 1 order, then update actions available
                if(a->getNumOrders()>0){
                    int index=-1;
                    Order update = a->updateOrder(index);
                    cout << "1. Add tickets to order\n2. Delete tickets from order\n3. Cancel Order\n";
                    achoice=0;
                    string seats="";
                    while (achoice<=0 || achoice>3){
                        cout << "Enter number:\t";
                        while (!(cin >> achoice)){
                            cout << "ERROR: a number must be entered: ";
                            cin.clear();
                            cin.ignore(123, '\n');
                        }
                        // Pass in auditorium information from the order and its data to add seats function
                        if (achoice==1) {
                            int at=0,ct=0,st=0;
                            if (update.getAud()==1)
                                seats=addSeats(A1, a1row, a1col, at, ct, st);
                            else if (update.getAud()==2)
                                seats=addSeats(A2, a2row, a2col, at, ct, st);
                            else if (update.getAud()==3)
                                seats=addSeats(A3, a3row, a3col, at, ct, st);
                            update.setAdult(update.getAdult()+at);
                            update.setChild(update.getChild()+ct);
                            update.setSenior(update.getSenior()+st);
                            update.setSeats(update.getSeats()+", "+seats);
                            a->repOrder(update,index);
                        }
                        // Pass in auditorium from the order and its seats to delete seats function
                        else if (achoice==2) {
                            char type=' ';
                            if (update.getAud()==1)
                                seats=deleteSeat(A1,update.getSeats(),type);
                            else if (update.getAud()==2)
                                seats=deleteSeat(A2,update.getSeats(),type);
                            else if (update.getAud()==3)
                                seats=deleteSeat(A3,update.getSeats(),type);
                            // updates all data from seat deleted in order
                            if(type=='A')
                                update.setAdult(update.getAdult()-1);
                            if(type=='C')
                                update.setChild(update.getChild()-1);
                            if(type=='S')
                                update.setSenior(update.getSenior()-1);
                            update.setSeats(seats);
                            a->repOrder(update,index);
                        }
                        // Pass in auditorium from the order and its seats to cancel seats function
                        else if (achoice==3) {
                            if (update.getAud()==1)
                                cancelSeats(A1,update.getSeats());
                            else if (update.getAud()==2)
                                cancelSeats(A2,update.getSeats());
                            else if (update.getAud()==3)
                                cancelSeats(A3,update.getSeats());
                            //cancels order from customer data
                            a->cancelOrder(index);
                        }
                    }
                }
                // if customer has no orders available
                else{
                    cout <<"No orders\n";
                }
            }
            // If user chooses to Print Receipt, then customer's printReceipt function is called
            else if (choice==4)
                a->printReceipt();
            // If user chooses to log out, then store user data to map and go back to beginning
            else if (choice==5){
                map[username] = *a;
                login=false;
            }
        }
    }
    //calls function to write final auditorium output to file
    printAudi(A1,a1row,a1col,"A1Final.txt");
    printAudi(A2,a2row,a2col,"A2Final.txt");
    printAudi(A3,a3row,a3col,"A3Final.txt");
    return 0;
}
