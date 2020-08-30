#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;

//enums used in switch cases to make the code more readable
enum user_choice{
  Add_new=1,
  Edit=2,
  Delete=3,
  Sort=4,
  Search=5,
  Exit=6
};

enum change_sort_and_search_option{
  By_name=1,
  By_surname=2,
  By_number=3,
  By_type=4,
  Done=5
};

//basic class that will form a phonebook
class Phone_Number{

  private:
    string name,
    surname,
    number,
    type;

  public:

    //methods used to abstract and encapsulate data
    //constructor
    Phone_Number(string name,string surname,string number,string type){
      this->name=name;
      this->surname=surname;
      this->number=number;
      this->type=type;
    }

    //methods to get data
    string get_name(){
      return this->name;
    }

    string get_surname(){
      return this->surname;
    }

    string get_type(){
      return this->type;
    }

    string get_number(){
      return this->number;
    }

    //methods to modify data
    void change_name(string change){
      this->name=change;
    }

    void change_surname(string change){
      this->surname=change;
    }

    void change_type(string change){
      this->type=change;
    }

    void change_number(string change){
      this->number=change;
    }

    //method to print information about object
    void print_user(){
        cout<<"\t"
        <<this->name<<" "
        <<this->surname<<" "
        <<this->number<<" "
        <<this->type<<"\n";
    }
};

class Phone_Book{
  private:
    vector <Phone_Number> phone_numbers;

  public:

    //return the phone numbers from the object
    vector <Phone_Number> get_numbers(){
      return this->phone_numbers;
    }

    //constructor
    Phone_Book(){
      load_data();
      user_interface();
    }

    //get inputs from the file
    void load_data(){
      ifstream read("phone_book.txt");
      string name,surname,number,type;
      while(!read.eof()){
        read
        >>name
        >>surname
        >>number
        >>type;
        this->phone_numbers.push_back(Phone_Number(name,surname,number,type));
      }
      cout<<"Data was loaded successfully!\n";
      system("pause");
      system("CLS");
    }

    //outputs information to the file for reuse later
    void save_data(){
        ofstream write("phone_book.txt");
        for(int i=0;i<int(phone_numbers.size());i++){
            write
            <<phone_numbers[i].get_name()<<" "
            <<phone_numbers[i].get_surname()<<" "
            <<phone_numbers[i].get_number()<<" "
            <<phone_numbers[i].get_type()<<"\n";
        }
        cout<<"Data was saved successfully !\n";
    }

    //the fuction to allow the user to interact with the app
    void user_interface(){
      system("CLS");
      cout<<"Welcome to your phonebook!\n\n";
      cout<<"We have some options for you:\n\n";
      cout<<"1.Add a user.\n";
      cout<<"2.Edit a user.\n";
      cout<<"3.Delete a user.\n";
      cout<<"4.Sort your numbers.\n";
      cout<<"5.Search a name or number.\n";
      cout<<"6.Exit.\n";
      int option;
      cin>>option;
      user_choice action=user_choice(option);
      system("CLS");
      switch(action){
        case Add_new:
          Add_user();
          break;
        case Edit:
          edit_user();
          break;
        case Delete:
          delete_user();
          break;
        case Sort:
          sort_data();
          break;
        case Search:
          search_data();
          break;
        case Exit:
          cout<<"Thank you for using our program!\nDo you want to save changes? (y/n)\n";
          char choice;
          cin>>choice;
          system("CLS");
          if(choice=='y'){
          save_data();}
          return;
      }
    }

    //gets input, creates and object from it and stores it in the end of our vector with phone numbers
    void Add_user(){
        string name,surname,number,type;
        cout<<"\nEnter the name of the new user:\n";
        cin>>name;
        system("CLS");
        cout<<"\nEnter the surname of the new user:\n";
        cin>>surname;
        system("CLS");
        cout<<"\nEnter the number of the new user:\n";
        cin>>number;
        system("CLS");
        cout<<"\nEnter the type of number of the new user:\n";
        cin>>type;
        system("CLS");
        phone_numbers.push_back(Phone_Number(name,surname,number,type));
        cout<<"Number has been added!\n";
        system("pause");
        system("CLS");
        user_interface();
    }

    //uses methods of the Phone_Number object to modify its data
    void edit_user(){
        system("CLS");
        string change;
        int option,place;
        cout<<"What do you want to change about this user?\n";
        cout<<"1.Name\n";
        cout<<"2.Surname\n";
        cout<<"3.Number\n";
        cout<<"4.Type\n";
        cout<<"5.I have done my changes take me back\n";
        cin>>option;
        system("CLS");
        change_sort_and_search_option action=change_sort_and_search_option(option);
        if(action!=Done){
            cout<<"Enter its place in the table and the new changed value: \n";
            cin>>place;
            if(place<int(phone_numbers.size())&&place>=0){
                phone_numbers[place-1].print_user();
                cin>>change;
            }
            else{
                cout<<"Sorry this number doesn't exist!\n";
                system("pause");
                user_interface();
            }
        }
        switch(action){
        case By_name:
            phone_numbers[place-1].change_name(change);
            edit_user();
            break;
        case By_surname:
            phone_numbers[place-1].change_surname(change);
            edit_user();
            break;
        case By_number:
            phone_numbers[place-1].change_number(change);
            edit_user();
            break;
        case By_type:
            phone_numbers[place-1].change_type(change);
            edit_user();
            break;
        case 5:
            cout<<"Number has been modified!\n";
            system("pause");
            system("CLS");
            user_interface();
        }
    }

    //deletes a object with a given position in our vector
    void delete_user(){
        int place;
        cout<<"Enter its place in the table: \n";
        cin>>place;
        if(place<int(phone_numbers.size())&&place>=0){
            phone_numbers.erase(phone_numbers.begin()+place-1);
            cout<<"Number has been deleted!\n";
        }
        else{
            cout<<"Sorry this number doesn't exist!\n";
        }
        system("pause");
        system("CLS");
        user_interface();
    }

    //data is sorted according to the choice of the user and printed in the screen
    void sort_data(){
      system("CLS");
      int option;
      cout<<"Do you want to sort users by: \n";
      cout<<"1.Name\n";
      cout<<"2.Surname\n";
      cout<<"3.Number\n";
      cout<<"4.Type\n";
      cin>>option;
      system("CLS");
      change_sort_and_search_option action=change_sort_and_search_option(option);
      switch(action){
        case By_name:
          sort(phone_numbers.begin(),phone_numbers.end(),sorting_by_name);
          break;
        case By_surname:
          sort(phone_numbers.begin(),phone_numbers.end(),sorting_by_surname);
          break;
        case By_number:
          sort(phone_numbers.begin(),phone_numbers.end(),sorting_by_number);
          break;
        case By_type:
          sort(phone_numbers.begin(),phone_numbers.end(),sorting_by_type);
          break;
        case Done:
            user_interface();
            return;
      }
      print_data(this->phone_numbers);
    }

    //sorting operators that our function above uses
    static bool sorting_by_name(Phone_Number A,Phone_Number B){
      return A.get_name()<B.get_name();
    }

    static bool sorting_by_surname(Phone_Number A,Phone_Number B){
      return A.get_surname()<B.get_surname();
    }

    static bool sorting_by_number(Phone_Number A,Phone_Number B){
      return A.get_number()<B.get_number();
    }

    static bool sorting_by_type(Phone_Number A,Phone_Number B){
      return A.get_type()<B.get_type();
    }

    //function to visualize the data we have currently in this object in the form of a simple table
    void print_data(vector <Phone_Number> these_phone_numbers){
      cout<<"Name\tSurname\tNumber\t\tType\n";
      for(int i=0;i<int(these_phone_numbers.size());i++){
        cout
        <<these_phone_numbers.at(i).get_name()<<"\t"
        <<these_phone_numbers.at(i).get_surname()<<"\t"
        <<these_phone_numbers.at(i).get_number()<<"\t"
        <<these_phone_numbers.at(i).get_type()<<"\n";
      }
      system("pause");
      system("CLS");
      user_interface();
    }

    //function that allows users to search for something in this phone book
    void search_data(){
      system("CLS");
      cout<<"Do you want to search users by :\n\n";
      cout<<"1.Name\n";
      cout<<"2.Surname\n";
      cout<<"3.Number\n";
      cout<<"4.Type\n";
      int option;
      cin>>option;
      change_sort_and_search_option action=change_sort_and_search_option(option);
      string search_term;
      system("CLS");
      if(action!=Done){
        cout<<"What do you want to search? (Careful! It is case sensitive!)\n\n";
        cin>>search_term;
      }
      system("CLS");
      switch(action){
        case By_name:
        print_data(find_by_name(search_term));
        break;
        case By_surname:
        print_data(find_by_surname(search_term));
        break;
        case By_number:
        print_data(find_by_number(search_term));
        break;
        case By_type:
        print_data(find_by_type(search_term));
        break;
        case Done:
        user_interface();
        return;
      }
    }

    //4 functions tasked to find objects that fulfill the search requirment and return them in the form of a vector
    vector <Phone_Number> find_by_name(string search_term){
      vector <Phone_Number> positive_result;
      for(int i=0;i<int(phone_numbers.size());i++){
        if(phone_numbers[i].get_name()==search_term){
          positive_result.push_back(phone_numbers[i]);
        }
      }
      return positive_result;
    }

    vector <Phone_Number> find_by_surname(string search_term){
      vector <Phone_Number> positive_result;
      for(int i=0;i<int(phone_numbers.size());i++){
        if(phone_numbers[i].get_surname()==search_term){
          positive_result.push_back(phone_numbers[i]);
        }
      }
      return positive_result;
    }

    vector <Phone_Number> find_by_number(string search_term){
      vector <Phone_Number> positive_result;
      for(int i=0;i<int(phone_numbers.size());i++){
        if(phone_numbers[i].get_number()==search_term){
          positive_result.push_back(phone_numbers[i]);
        }
      }
      return positive_result;
    }

    vector <Phone_Number> find_by_type(string search_term){
      vector <Phone_Number> positive_result;
      for(int i=0;i<int(phone_numbers.size());i++){
        if(phone_numbers[i].get_type()==search_term){
          positive_result.push_back(phone_numbers[i]);
        }
      }
      return positive_result;
    }

};

//in the main function we just create a instance of this class and its constructor does the work by loading data and showing the user_interface
int main() {
  Phone_Book new_phone_book;
}
