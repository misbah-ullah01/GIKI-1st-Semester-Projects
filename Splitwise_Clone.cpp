#include <iostream>
#include <fstream>
using namespace std;

bool isNumber(string a);
int toNumber(string a);
void printInterface();
void askChoice();
void getData();
void createGroup();
void addExpenses();
void settleUp();
void displayExpenses();
void readData();
void writeData();
void restoreVariables();
string lowercase(string a);

const int MAX_ACCOUNTS = 50, MAX_GROUPS = 5, MAX_PEOPLE_P_GROUP = MAX_ACCOUNTS / MAX_GROUPS;
bool loggedIn = false;
int accounts_opened = 0, groups_formed = 0, choice = 0, memebers_in_group[MAX_GROUPS] = {0};

/*
   Name, ID, Password
   Groups, (1. Name 2. Money member ows), Members in each group
*/

string user_data[MAX_ACCOUNTS][3],
    groups[MAX_GROUPS][MAX_PEOPLE_P_GROUP][2],
    group_names[MAX_GROUPS],
    persons_tobe_paid[MAX_GROUPS], name, id, password;

int main()
{
    restoreVariables();
    readData();

    cout << "\n\t\t\t~~~~~~~~~~ WELCOME TO SPLIT-WISE APPLICATION ~~~~~~~~~~\n\n";
    while (choice != 6)
    {
        printInterface();
        askChoice();
        switch (choice)
        {
        case 1:
            getData();
            break;
        case 2:
            createGroup();
            break;
        case 3:
            addExpenses();
            break;
        case 4:
            settleUp();
            break;
        case 5:
            displayExpenses();
            break;
        }
    }
    writeData();
    return 0;
}

bool isNumber(string a)
{
    int length = a.length();
    for (int i = 0; i < length; i++)
    {
        if (a[i] < '0' || a[i] > '9')
            return false;
    }
    return true;
}
int toNumber(string a)
{
    int length = a.length(), num = 0, x = 1;
    for (int i = length - 1; i >= 0; i--, x *= 10)
    {
        num += (a[i] - '0') * x;
    }
    return num;
}
void printInterface()
{
    if (!loggedIn)
    {
        cout << "\t\t\t1. Login/Signup\n"
             << "\t\t\t6. Exit\n"
             << "Please select your Choice: ";
        // << "2. Create Groups\n"
        // << "3. Add Expenses\n"
        // << "4. Settle Up\n"
        // << "5. Display Expense Details\n"
    }
    else
    {
        cout << "\t\t\t1. Logout\n"
             << "\t\t\t2. Create Groups\n"
             << "\t\t\t3. Add Expenses\n"
             << "\t\t\t4. Settle Up\n"
             << "\t\t\t5. Display Expense Details\n"
             << "\t\t\t6. Exit\n"
             << "Please select your Choice: ";
    }
}
void askChoice()
{
    do
        cin >> choice;
    while (choice < 1 || choice > 6);
    if (choice == 6)
        cout << "\n\t\t**********   THAKNS FOR USING :) **********\n";
}
void getData()
{
    if (loggedIn)
    {
        cout << "\n\t\tLOGGED OUT SUCCESSFULY !\n";
        loggedIn = false;
        return;
    }
    int choice;
    do
    {
        cout << "\n\t\t\t1. Login\n\t\t\t2. Signup\nPlease select Choice: ";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    if (choice == 1)
    {
        cout << "\n\tEnter your name: ";
        cin >> name;
        cout << "\tEnter your ID: ";
        cin >> id;
        cout << "\tEnter your Password: ";
        cin >> password;
        for (int i = 0; i < accounts_opened; i++)
        {
            if (name == user_data[i][0] &&
                id == user_data[i][1] &&
                password == user_data[i][2])
            {
                loggedIn = true;
                cout << "\n\t\t #######~~ Welcome " << user_data[i][0] << " ~~#######\n";
                name = lowercase(name);
            }
        }
        if (!loggedIn)
            cout << "\n\t~~~~~   Your account doesn't exist!   ~~~~~\n";
    }
    else
    {
        bool uniqueID;
        cout << "\n\tEnter your name: ";
        cin >> user_data[accounts_opened][0];

        cout << "\tEnter your ID: ";
        do
        {
            uniqueID = true;
            cin >> user_data[accounts_opened][1];
            for (int i = 0; i < accounts_opened; i++)
            {
                if (user_data[i][1] == user_data[accounts_opened][1])
                    uniqueID = false;
            }
            if (!uniqueID)
                cout << "\n\t## This ID is already taken. ##\n";
        } while (!uniqueID);

        cout << "\tEnter your Password: ";
        cin >> user_data[accounts_opened][2];
        cout << "\n$$ Your Account has been opened :)\n\t~~~ PLEASE LOGIN AGAIN ~~~\n";
        user_data[accounts_opened][0] = lowercase(user_data[accounts_opened][0]);
        accounts_opened++;
    }
}
void createGroup()
{
    if (!loggedIn)
    {
        cout << "\n\t!!_PLEASE LOGIN FIRST_!!.\n";
        return;
    }
    string a;
    cout << "\n\tEnter the name of the group: ";
    cin >> group_names[groups_formed];
    cout << "\tEnter the number of memebers you want to add: ";
    do
    {
        if (memebers_in_group[groups_formed] < 0)
        {
            cout << "\n\t##==> Please enter a valid value: ";
        }
        else if (memebers_in_group[groups_formed] > 10)
        {
            cout << "\n\t##==> You can't add more than 10 members.\n";
        }
        cin >> memebers_in_group[groups_formed];
    } while (memebers_in_group[groups_formed] > 10 || memebers_in_group[groups_formed] < 0);

    int members = memebers_in_group[groups_formed];
    for (int i = 0; i < members; i++)
    {
        cout << "Name: ";
        cin >> groups[groups_formed][i][0];
        groups[groups_formed][i][1] = "0";
    }
    groups_formed++;
}
void addExpenses()
{
    if (!loggedIn)
    {
        cout << "\n\t!!_PLEASE LOGIN FIRST_!!.\n";
        return;
    }
    string a, person_paid_name;
    bool groupFound = false, isMember = false;
    int index;
    do
    {
        cout << "\n\tEnter the group name: ";
        cin >> a;
        for (index = 0; (index < groups_formed && !groupFound); index++)
        {
            if (group_names[index] == a)
            {
                groupFound = true;
                index--;
            }
        }
    } while (!groupFound);

    int members = memebers_in_group[index], total_expense, no_of_members_involved, choice, total_sum;
    for (int i = 0; (i < members && !isMember); i++)
    {
        if (name == groups[index][i][0])
        {
            isMember = true;
        }
    }
    if (!isMember)
    {
        cout << "\n##==> You can't access this group\n";
        return;
    }

    cout << "\n\tEnter the total expense: ";
    cin >> total_expense;
    cout << "\tEnter the index of person who paid: \n";

    for (int i = 0; i < members; i++)
    {
        cout << i + 1 << ". " << groups[index][i][0] << "\n";
    }
    do
        cin >> choice;
    while (choice < 0 || choice > members);

    persons_tobe_paid[index] = groups[index][choice - 1][0];

    cout << "\nNo. of members involved in expense: ";
    do
        cin >> no_of_members_involved;
    while (no_of_members_involved < 0 || no_of_members_involved > members);

    string involved_members_names[no_of_members_involved];

    if (no_of_members_involved != members)
    {
        cout << "\nPlease enter indexes of persons involved: \n";
        for (int i = 0; (i < members); i++)
        {
            cout << i + 1 << ". " << groups[index][i][0] << "\n";
        }
        int choices[no_of_members_involved];
        for (int i = 0; i < no_of_members_involved; i++)
        {
            do
                cin >> choices[i];
            while (choices[i] <= 0 || choices[i] > members);
        }
        for (int i = 0; i < no_of_members_involved; i++)
        {
            involved_members_names[i] = groups[index][choices[i] - 1][0];
        }
    }

    do
    {
        cout << "\n\tHow do you want to split?\n"
             << "\t\t1. Equally\n"
             << "\t\t2. Unequally\n"
             << "Please enter your Choice: ";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    float share = total_expense / no_of_members_involved;
    if (no_of_members_involved == members)
    {
        do
        {
            total_sum = 0;
            for (int i = 0; i < members; i++)
            {
                if (choice == 1)
                {
                    groups[index][i][1] = to_string(share);
                }
                else
                {
                    cout << groups[index][i][0] << ": ";
                    cin >> groups[index][i][1];
                    total_sum += toNumber(groups[index][i][1]);
                }
            }
            if (total_expense != total_sum)
            {
                cout << "\nPlease split whole expense\n";
            }
        } while (choice == 2 && total_sum != total_expense);
    }
    else
    {
        do
        {
            total_sum = 0;
            for (int i = 0; i < no_of_members_involved; i++)
            {
                for (int j = 0; j < members; j++)
                {
                    if (involved_members_names[i] == groups[index][j][0])
                    {
                        if (choice == 1)
                        {
                            groups[index][j][1] = to_string(share);
                        }
                        else
                        {
                            cout << groups[index][j][0] << ": ";
                            cin >> groups[index][j][1];
                            total_sum += toNumber(groups[index][j][1]);
                        }
                    }
                }
            }
        } while (choice == 2 && (total_expense != total_sum));
        for (int i = 0; i < members; i++)
        {
            bool isInvolved = false;
            for (int j = 0; j < no_of_members_involved; j++)
            {
                if (groups[index][i][0] == involved_members_names[j])
                {
                    isInvolved = true;
                }
            }
            if (!isInvolved)
            {
                groups[index][i][1] = "0";
            }
        }
    }
}
void settleUp()
{
    if (!loggedIn)
    {
        cout << "\n\t!!_PLEASE LOGIN FIRST_!!.\n";
        return;
    }
    string a;
    cout << "\n\tEnter your group name: ";
    cin >> a;
    int i = 0;
    for (; (i < groups_formed && group_names[i] != a); i++)
    {
    }
    cout << "\n\tGroup: " << group_names[i] << "\n";
    for (int j = 0; j < memebers_in_group[i]; j++)
    {
        cout << "\t" << groups[i][j][0] << ": " << groups[i][j][1] << "\n";
    }
    if (persons_tobe_paid[i] != "")
    {
        cout << "\n\tAll members need to pay to " << persons_tobe_paid[i] << "\n";
    }
}
void displayExpenses()
{
    if (!loggedIn)
    {
        cout << "\n\t!!_PLEASE LOGIN FIRST_!!.\n";
        return;
    }
    for (int i = 0; i < groups_formed; i++)
    {
        bool isMember = false;
        for (int j = 0; (j < memebers_in_group[i] && !isMember); j++)
        {
            if (name == groups[i][j][0])
                isMember = true;
        }
        if (!isMember)
        {
            continue;
        }
        cout << "\n\tGroup: " << group_names[i] << "\n";
        for (int j = 0; j < memebers_in_group[i]; j++)
        {
            cout << "\t" << groups[i][j][0] << ": " << groups[i][j][1] << "\n";
        }
        cout << "\n\tAll members need to pay to " << persons_tobe_paid[i] << "\n\n\n";
    }
}
void writeData()
{
    ofstream write_file("groups.txt", ios::out);
    ofstream write_variables("variables.txt", ios::out);
    ofstream write_users("users.txt", ios::out);

    for (int i = 0; i < groups_formed; i++)
    {
        write_file << "\n\tGroup " << group_names[i] << "\n";
        for (int j = 0; j < memebers_in_group[i]; j++)
        {
            write_file << groups[i][j][0] << " " << groups[i][j][1] << "\n";
        }
        write_file << persons_tobe_paid[i] << "\n";
    }
    write_variables << accounts_opened << " " << groups_formed << "\n";
    for (int i = 0; i < groups_formed; i++)
    {
        write_variables << memebers_in_group[i] << " ";
    }
    for (int i = 0; i < accounts_opened; i++)
    {
        write_users << user_data[i][0] << " " << user_data[i][1] << " " << user_data[i][2] << "\n";
    }
    write_file.close();
    write_variables.close();
    write_users.close();
}
void readData()
{
    ifstream read_groups("groups.txt");
    ifstream read_users("users.txt");
    string buffer;
    for (int i = 0; i < groups_formed; i++)
    {
        read_groups >> buffer >> group_names[i];
        for (int j = 0; j < memebers_in_group[i]; j++)
        {
            read_groups >> groups[i][j][0] >> groups[i][j][1];
        }
        read_groups >> persons_tobe_paid[i];
    }
    for (int i = 0; i < accounts_opened; i++)
    {
        read_users >> user_data[i][0] >> user_data[i][1] >> user_data[i][2];
    }
    read_groups.close();
    read_users.close();
}
void restoreVariables()
{
    ifstream variables("variables.txt");
    int i = 0;
    string buffer;
    variables >> accounts_opened >> groups_formed;
    while (variables >> buffer)
    {
        if (isNumber(buffer))
            memebers_in_group[i++] = toNumber(buffer);
    }
    variables.close();
}
string lowercase(string a)
{
    for (int i = 0, n = a.length(); i < n; i++)
    {
        if (a[i] >= 'A' && a[i] <= 'Z')
        {
            a[i] += 32;
        }
    }
    return a;
}
