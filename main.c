#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int day,month,year;
} Date;
typedef struct
{
    char f_name[20],l_name[20],address[50],num[16],mail[40];
    Date DoB;
} Contact;

Contact c[100]; //Array of contacts, will be filled with all contacts in the file.
int n=0; //Global variable representing the number of contacts in the file.
char fileName[50]; //Global variable used to store the name of the text file.

void loadFile(); //Scan file name, read all data from the file, and put it in the array of contacts.
int input(char *x); //Input an integer and check whether it is an integer or not.
void funcSelect(int opt); //Select the function you want to use.
void phonebookOpts(); //Display the menu, all options in our program.
void back(); //Asks the user whether to go back to menu or exit.
void saveFile(); //Save all changes in the file.
void quit(); //Quit without saving.
void decide(); //User decides whether he wants to save the changes made in the file, or go back to menu.
int checkNum(char nmb[12], int except); //Validation of the phone number entered by the user.
int checkDate(int d,int m,int y); //Validation of the date of birth entered by the user.
int check_mail(char x[], int except); //Validation of the email entered by the user.
void searchFile(); //Search for a contact in the file.
void enter_data(int x); //Function used in both "add_contact" and "modify_contact" to prompt the user for the contact's data.
void add_contact(); //Add a contact to the file.
void delete_contact(); //Delete a contact from the file.
void modify_contact(); //Modify a contact in the file
int swap (Contact *x, Contact *y); //Swap two contacts in the array.
void sortByLname(); //Sort all contacts by last name in ascending order.
void sortByDoB(); //Sort all contacts by date of birth in ascending order.
void printFile(); //Print all contacts in the file, sorted by last name or date of birth.

int main()
{
    loadFile(); //Load the file and fill the contacts array.
    phonebookOpts(); //Display the menu.
    return 0;
}
void loadFile()
{
    printf("Please enter the name of the file you want to load: "); //User is prompted to enter the file name and extension
    scanf("%s",fileName);
    strcat(fileName,".txt");
    FILE*f=fopen(fileName,"r"); //Open the file in a read mode.
    if(!f)
    { //If the file can not be opened, the user will be asked whether he would like to re-enter its name or create a new one
        printf("\nFILE CANNOT BE OPENED!  Please choose one of the following options:\n\t(1)\tRe-enter file name\n\t(2)\tCreate a file with this name\nYour choice: ");
        int z;
        do{
            char x[4];
            z = input(x); //Prompt the user for his choice and check whether it is an integer or not.
            if (z!=1&&z!=2)
                printf("NOT FOUND!\nPlease re-enter your choice: ");
        }while (z!=1&&z!=2);
        switch(z)
        {
            case 1: loadFile(); break;  //Function will be recalled so the user can re-enter his choice.
            case 2: printf("A new file with the name %s is created in your directory\n",fileName);saveFile(); break; //User will be asked to add a contact.
            default: break;
        }
    }
    else //If the file exists and can be opened.
    {
        int stPos,edPos; //Variables storing start and end position of the cursor in file
        stPos=ftell(f);
        fseek(f,0,SEEK_END);
        edPos=ftell(f);
        if(stPos!=edPos){ //If the beginning of the file is the same as its end(File is empty), scanning will not be made.
            rewind(f); //Return cursor to the beginning of the file
            while(!feof(f)) //Loop until the end of the file, for each contact get all its data and put the contact in the array.
            {
                fscanf(f,"%[^,],",c[n].l_name);
                fscanf(f,"%[^,],",c[n].f_name);
                fscanf(f,"%d-%d-%d,",&c[n].DoB.day,&c[n].DoB.month,&c[n].DoB.year);
                fscanf(f,"%[^,],",c[n].address);
                fscanf(f,"%[^,],",c[n].num);
                fscanf(f,"%s\n",c[n].mail);
                n++; //n is a global variable starting with 0, is incremented by 1 after each loop, so after reaching the end of the file n will be equal to the number of contacts in the file.
            }}
        else printf("FILE IS EMPTY!\nYou have to add a contact!\n");
        fclose(f); //Close the file.
    }
}
int input(char *x)
{
    int i;
    do{
    scanf("%s", x); //scan the number entered by the user in a string.
    i=atoi(x); //Convert the string to a integer.
    if (i==0) //i will be equal to 0 if no valid conversion takes place.
        printf("INVALID CHARACTER INPUT!\nPlease re-enter your choice: ");
    }while(i==0);
    return i; //The integer is returned
}
void funcSelect(int opt)
{
    switch(opt) //Variable "opt" is the choice made by the user, and according to it the function will be called.
    {
        case 1: searchFile(); break;
        case 2: add_contact(); break;
        case 3: delete_contact(); break;
        case 4: modify_contact(); break;
        case 5: printFile(); break;
        case 6: saveFile(); break;
        case 7: quit(); break;
        default: //If the user chooses a number which is not from the options, he will be asked to re-enter the number.
            printf("INVALID CHOICE!\nPlease re-enter your choice: ");
            char x[4];
            opt=input(x);
            funcSelect(opt);
            break;
    }
}
void phonebookOpts()
{
    char x[4];
    printf("\t\tPhonebook options\n\t(1)\t\tSearch for a contact\n\t(2)\t\tAdd a contact\n\t(3)\t\tDelete a contact\n\t(4)\t\tModify a contact\n\t(5)\t\tPrint phonebook\n\t(6)\t\tSave to file\n\t(7)\t\tExit programme\n\tSelect an option from the menu:\t");
    int opt=input(x); //Prompt the user for his choice, check whether it is an integer.
    funcSelect(opt); //Call the function selected.
}
void back()
{
    printf("\nDo you want to go back to menu(Y or N)? "); //The user is asked if he wants to go back to the main menu.
    char ch;
    scanf(" %c",&ch);
    while((ch!='Y'&&ch!='y')&&(ch!='N'&&ch!='n'))
    {
        printf("\nINVALID INPUT!\nPlease re-enter your choice: ");
        scanf(" %c",&ch);
    }
    if(ch=='Y'||ch=='y')
        phonebookOpts(); //If the user said YES, the menu is displayed.
    else if(ch=='N'||ch=='n')
    {
        printf("\nTHANK YOU!\n"); //If the user said NO, he will exit the programme.
        exit(0);
    }
}
void saveFile()
{
    int i;
    FILE*f=fopen(fileName,"w"); //Open the file in write mode to re-enter the contacts.
    if(!f)
    {
        printf("FILE CANNOT BE SAVED!");
        exit(1);
    } //Exit if the file can not be opened.
    for(i=0;i<n;i++) // Loop until the end of the array.
    {
        fprintf(f,"%s,%s,%d-%d-%d,%s,%s,%s\n",c[i].l_name,c[i].f_name,c[i].DoB.day,c[i].DoB.month,c[i].DoB.year,c[i].address,c[i].num,c[i].mail); //Print all contacts in the file.
    }
    fclose(f);
    if(n)
        printf("\nDATA SAVED SUCCESSFULLY TO FILE!");
    back();
}
void quit()
{
    char ch;
    printf("\nAll changes will be discarded unless you saved it before\nAre you sure you want to quit(Y or N)? ");
    scanf(" %c",&ch);
    while((ch!='Y'&&ch!='y')&&(ch!='N'&&ch!='n')) //If the user wants to quit he is only allowed to type 'Y'or 'y', if not he can type 'N' or 'n'.
    {
        printf("INVALID INPUT!\nPlease re-enter your choice: ");
        scanf(" %c",&ch);
    }
    if(ch=='Y'||ch=='y'){ //If the user said YES, changes will not be saved.
        printf("\nTHANK YOU!\n");
        exit(0);
        }
    else //If the user said NO, he will be asked whether he would like to go back to menu or not.
        back();
}
void decide()
{
    printf("\n\t\tDo you want to save or go back to menu\n\t(1)\t\tSave to file\n\t(2)\t\tGo back to menu\nSelect an option from the menu: "); //Ask the user if he wants to save or quit.
    int z;
    do{
        char x[4];
        z = input(x); //Prompt the user for his choice and check whether it is an integer or not.
        if (z!=1&&z!=2)
            printf("INVALID CHOICE!\nPlease re-enter your choice: ");
    }while (z!=1&&z!=2);
    switch(z)
    {
        case 1: saveFile(); break; //Changes will be saved in the file.
        case 2: phonebookOpts(); break; //Main menu will be displayed.
        default: break;
    }
}
void searchFile()
{//Linear Search
    char cname[20];
    printf("\nSEARCH FOR A CONTACT\nPlease enter contact last name:\t");
    scanf("%s",cname); //The last name the user wants to search is stored in variable cname.
    int i,cnt=0;
    for(i=0; i<n; i++) //Loop on all the contacts of file.
    {
        if(strcmp(c[i].l_name,cname)==0) //When the contact the user searched is found, the data of this contact will be printed.
        {
            printf("\nContact %d\nFirst name: %s\tAddress: %s\tEmail: %s\tPhone number: %s\n",cnt+1,c[i].f_name,c[i].address,c[i].mail,c[i].num);
            cnt++; //When a contact with this last name is found, this variable is incremented by 1.
        }
    }
    if(cnt==0) //If this variable equals to 0, that means that it has not been incremented, so no contacts are found.
        printf("\nNO MATCHES FOUND!\n");
    back(); //The user is asked if he wants to go back to menu.
}
int checkNum(char nmb[16], int except) //the input of this function is the phone number to check, and except which is the position of the contact to check.
{
    int i,nl=strlen(nmb);
    if(nl<6||nl>15)
    {
        printf("INVALID PHONE NUMBER LENGTH!\n");
        return 1;
    }
    for(i=0; i<nl; i++) //Check that the phone number consists only of digits (0-9).
    {
        if(nmb[i]<48||nmb[i]>57) //According to the ASCII table, a digit is between 48 and 57, so any character in the phone number out of this range is incorrect.
        {
            printf("INVALID CHARACTER INPUT!\n");
            return 1;
        }
    }
    for(i=0;i<n&&i!=except;i++) //Check whether another contact has the same phone number.
    {
        if(strcmp(c[i].num,nmb)==0){
            printf("NUMBER ALREADY EXISTS!\n");
            return 1;}
    }
    return 0; //Returns 0 if the phone number is valid.
}
int checkDate(int d,int m,int y) //d, m and y are the day, month and year entered by the user respectively.
{
    if (y>2021) //Check that the year has passed.
    {
        printf("INVALID YEAR\n");
        return 1;
    }
    if (m<1 || m>12) //Check that the month is between 1 and 12.
    {
        printf("INVALID MONTH\n");
        return 1;
    }
    if (d<1 || d>31) //Check that the day is between 1 and 31.
    {
        printf("INVALID DAY\n");
        return 1;
    }
    if (d==31 && (m==4 || m==6 || m==9 || m==11)) //Check that there is 31 days in this month.
    {
        printf("THIS MONTH DOES NOT HAVE 31 DAYS\n");
        return 1;
    }
    if (m==2 && d>29) //Check that February has not more than 29 days.
    {
        printf("FEBRUARY DOES NOT HAVE MORE THAN 29 DAYS\n");
        return 1;
    }
    if (m==2 && d==29 && (y%400 != 0 && (y%4!=0 || y%100==0))) //Check if it is a leap year and February has 29 days.
    {
        printf("FEBRUARY ONLY HAS 28 DAYS IN THIS YEAR\n");
        return 1;
    }
    return 0; //It is valid date when all the previous conditions were false.
}
int check_mail(char x[], int except) //x is the mail entered by the user, except is the position of the contact to check.
{
    int i,length=strlen(x),j,found=0;
    char domain[15]; //Checking that the domain is valid.
    for (i=0;i<n;i++) //Check whether another contact has the same email.
    {
        if(!strcmp(x,c[i].mail)&&i!=except)
        {
            printf("EMAIL ALREADY EXISTS!\n");
            return 1; //Invalid email.
        }
    }
    for(i=0;i<length;i++) //Find the position of '@' in the email address.
    {
        if(x[i]=='@')
            {
                j=i; //j is the index of '@'
                found=1;
                break;
            }
    }
    if(!found)
    {
        printf("INVALID INPUT\n");
        return 1;
    }
    for(i=0;i<length;i++) //Checking that the email address before only consists of digits, characters (a-z) or (A-Z), underscore or '.' or '-'.
    {
        if((i!=j) && !(x[i]=='_'||x[i]=='.'||x[i]=='-'||(x[i]>47&&x[i]<58)||(x[i]>64&&x[i]<91)||(x[i]>96&&x[i]<123)))
        {
            printf("INVALID INPUT!\n");
            return 1;
        }
    }
    strcpy(domain, x+j+1); //Copy the part of the email address after the '@'.
    if(strcmp(x+length-4,".com")!= 0 || (strlen(domain)<6)) //Checking that the email ends with ".com" and that the domain length is bigger than 4.
    {
        printf("INVALID DOMAIN!\n");
        return 1;
    }
    return 0; //Email is valid.
}
void enter_data(int x) //x is the position the contact added or modified
{
    //User is prompted field by field for the data of the new contact.
    printf("First name: ");
    scanf("%s", c[x].f_name);
    printf("Last name: ");
    scanf("%s", c[x].l_name);
    printf("Birth date(day-month-year): ");
    scanf("%d-%d-%d", &c[x].DoB.day, &c[x].DoB.month, &c[x].DoB.year);
    int w=checkDate(c[x].DoB.day,c[x].DoB.month,c[x].DoB.year); //Validation of the date.
    while(w) //While is true when "w" != 0, that means that the date entered was incorrect.
    {
        printf("Please re-enter birth date(day-month-year): ");
        scanf("%d-%d-%d", &c[x].DoB.day, &c[x].DoB.month, &c[x].DoB.year);
        w=checkDate(c[x].DoB.day,c[x].DoB.month,c[x].DoB.year);
    }
    printf("Address: ");
    scanf(" %[^\n]", c[x].address);
    printf("Phone number: ");
    scanf("%s", c[x].num);
    w=checkNum(c[x].num,x);
    while(w) //While is true when "w" != 0, that means that the phone number entered was incorrect.
    {
        printf("Please re-enter phone number: ");
        scanf("%s",c[x].num);
        w=checkNum(c[x].num,x);
    }
    printf("Email: ");
    scanf("%s", c[x].mail);
    w=check_mail(c[x].mail, x);
    while(w) //While is true when "w" != 0, that means that the email entered was incorrect.
    {
        printf("Please re-enter the email: ");
        scanf("%s", c[x].mail);
        w=check_mail(c[x].mail, x);
    }
}
void add_contact()
{
    printf("\nADD CONTACT\nPlease enter data of the new contact: \n");
    enter_data(n); //Here the user will be asked to enter all data of the new contact.
    n++; //Global variable n is incremented by 1, because a new contact was added.
    decide(); //Ask the user if he wants to save or go back to menu.
}
void delete_contact()
{
    int i,j,k=0,index[n],m=0,z=0;
    char cfname[20],clname[20];
    printf("\nDELETE CONTACT\nPlease enter contact first name: ");  //Prompt the user for the first and last name of the contact he wants to delete.
    scanf("%s",cfname);
    printf("Please enter contact last name: ");
    scanf("%s",clname);
    for (i=0;i<n;i++) //Looping on all contacts, searching for contacts with these first and last name.
    {
        if (strcmp(c[i].l_name,clname)==0&&strcmp(c[i].f_name,cfname)==0) //When a contact is found, it will be displayed to the user.
        {
            printf("\nContact to be deleted:\nDate of Birth: %d-%d-%d\tPhone number: %s\n",c[i].DoB.day,c[i].DoB.month,c[i].DoB.year,c[i].num);
            index[k] = i; //index is an array of integers that will contain the index of each contact to be deleted.
            k++; //k starting by 0, incremented by 1 each time a contact is found, so will finally represent the number of contacts to be deleted.
        }
    }
    if (!k) //if k=0, that means that no contacts were found.
    {
        printf("\nNO CONTACTS FOUND!\n");
        back(); //Ask the user if he wants to go back to menu.
    }
    else
    {
        for(i=0;i<k;i++) //Looping a number of time equals the number of contacts to be deleted.
        {
            for(j=index[m]-z;j<n-1;j++) //Start from the first contact to be deleted, replace each contact by the one after it.
            {
                c[j]=c[j+1];
            }
            z++; //z is incremented by 1 because all the contacts were shifted to the left, so the next time in the loop we want to start from the index of the next contact to be deleted but decremented by 1.
            n--;m++; //n is decremented by 1 because a contact was deleted, m is incremented to get the index of the next contact to be deleted.
        }
        decide();//Decide to save or go back to menu.
    }
}
void modify_contact()
{
    int i,index[n],k=0,x,j;
    char cname[20];
    printf("\nMODIFY CONTACT\nPlease enter contact last name:\t"); //Prompt the user for the last name of the contact he wants to modify.
    scanf("%s",cname);
    for(i=0;i<n;i++) //Looping on all contacts, searching for contacts with this last name.
    {
        if (strcmp(c[i].l_name,cname)==0)
        {
            index[k]=i; //index is an array of integers that will contain the index of each contact to be modified.
            k++; //k starting by 0, incremented by 1 each time a contact is found, so will finally represent the number of contacts to be modified.
        }
    }
    if(!k) //if k=0, that means that no contacts were found.
    {
        printf("\nNO CONTACTS FOUND!\n");
        back(); //Ask the user if he wants to go back to menu.
    }
    else
    {
        if(k>1) //If there is more than one contact with this last name, display these contacts and let the user choose which one does he want to modify.
        {
            for(i=0;i<k;i++)
                {
                    printf("\n(%d) %s %s\tEmail: %s\tPhone Number: %s\n", i+1, c[index[i]].f_name, c[index[i]].l_name, c[index[i]].mail, c[index[i]].num); //Data of contacts with this last name.
                }
            printf("\nPlease choose which contact do you want to modify: ");
            char p[4];
            do{
                j=input(p); //The user is prompted for his choice.
                if (j>k) //If the user entered a number higher than the possible ones.
                    printf("INVALID CHOICE!\nPlease re-enter your choice: ");
            }while(j>k); //Loop until he choose a valid number.
            x=index[j-1]; //x represents the index of the contact to be modified.
        }
        else
        {
            x=index[0]; //If only one contact was found with this last name, x will be equal to the first and only element in the array.
        }
        printf("\nContact to be modified: \n%s %s\tDate of Birth: %d-%d-%d\tEmail: %s\tAddress: %s\tPhone Number: %s\n", c[x].f_name,c[x].l_name,c[x].DoB.day,c[x].DoB.month,c[x].DoB.year,c[x].mail,c[x].address,c[x].num);
        printf("\nModify the data: \n");
        enter_data(x); //Prompting the user field by field for the data of the contact he wants  to modify.
        decide();//Ask the user if he wants to save or go back to menu.
   }
}
int swap (Contact *x, Contact *y)
{
    //Swap function takes as input the addresses of 2 contacts and returns 0.
    Contact temp;
    temp = *x;
    *x = *y;
    *y = temp;
    return 0;
}
void sortByLname()
{//Bubble Sort
    int pass,i,sorted=0;
    for (pass=1;!sorted&&pass<n;pass++) //Loop until you reach the end of the array or when sorted = 1.
    {
        sorted=1; //When the array is sorted, 'sorted' will remain = 1, and the loop will end.
        for (i=0;i<n-pass;i++)
        {
            if (strcmp(c[i].l_name, c[i+1].l_name)==1) //When contact 2 is less than contact 1, they will be swapped.
                sorted=swap(&c[i],&c[i+1]); //Swap function returns 0 when executed.
            if (strcmp(c[i].l_name, c[i+1].l_name)==0) //When two contacts have the same last name, they will be sorted by first name.
                if (strcmp(c[i].f_name, c[i+1].f_name)==1)
                    sorted=swap(&c[i],&c[i+1]);
        } //After this loop, the higher contact in order will be the last one.
    }
}
void sortByDoB()
{//Bubble Sort
    int i,j,sorted=0;
    for(i=1;!sorted&&i<n;i++) //Loop until you reach the end of the array or when sorted = 1.
    {
        sorted = 1; //When the array is sorted, 'sorted' will remain = 1, and the loop will end.
        for(j=0;j<n-i;j++)
        {
            if(c[j].DoB.year>c[j+1].DoB.year) //Check year, if contact 1 higher than contact 2, they will be swapped.
                sorted=swap(&c[j],&c[j+1]);
            else if(c[j].DoB.year==c[j+1].DoB.year)
            {
                if(c[j].DoB.month>c[j+1].DoB.month) //If they have the same year, but contact 1 month higher than contact 2, they will be swapped.
                    sorted=swap(&c[j],&c[j+1]);
                else if(c[j].DoB.month==c[j+1].DoB.month)
                     if(c[j].DoB.day>c[j+1].DoB.day) //If the have the same year and month, but contact 1 day higher than contact 2, they will be swapped.
                        sorted=swap(&c[j],&c[j+1]);
            }
        } //After this loop, the higher contact in order will be the last one.
    }
}
void printFile()
{
    if (n==0) //If the file is empty.
    {
        printf("\nNO CONTACTS FOUND.\n");
        back();
    }
    else
    {
        //Ask the user if he wants to print the contacts sorted by last name or date of birth.
        printf("\nPRINTING FILE\n\t\tPrinting options\n\t(1)\t\tSorted by last name\n\t(2)\t\tSorted by date of birth\n\tSelect an option from the menu: ");
        int z;
        do{
            char x[4];
            z = input(x); //Prompt the user for his choice.
            if (z!=1&&z!=2)
                printf("INVALID CHOICE!\nPlease re-enter printing option: ");
        }while (z!=1&&z!=2); //Loop if the user entered invalid number.
        switch(z)
        {
            case 1: sortByLname(); break; //Sort them by last name.
            case 2: sortByDoB(); break; //Sort them by date of birth.
            default: break;
        }
        int i;
        for(i=0; i<n; i++) //After sorting contacts, print them.
        {
            printf("Contact %d\nFirst name: %s  Last name: %s  Birth date: %d-%d-%d  Address: %s  Phone: %s  Email: %s\n",i+1,c[i].f_name,c[i].l_name,c[i].DoB.day,c[i].DoB.month,c[i].DoB.year,c[i].address,c[i].num,c[i].mail);
        }
        decide(); //Ask the user if he wants to save or go back to menu.
    }
}
