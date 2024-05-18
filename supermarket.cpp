#include <fstream>
#include <iomanip> //https://cplusplus.com/reference/iomanip/setw/
#include <iostream>
#include <sstream>
#include <string>
#include <time.h> //https://cplusplus.com/reference/ctime/
#include <vector>
/**************************************************************
The struct date is for getting dates divided by day, month, and year.
**************************************************************/
struct date {
  int day, month, year;
};
/**************************************************************
The struct items defines groups of items in the data.txt file.
It also defines the types of values they hold.
***************************************************************/
struct items {
  std::string name, DOE_str;
  date DOE;
  std::string type;
  int quantity;
  float price;
};
/*****************************************************************
The searchItem() function takes a vector of items and a string of name as
arguments. This function prompts the user to enter the name of the item
they are looking for and gets it via cin. After that, the function searches
through a vector of "items" to discover the index of the item that fits the
user's search query. If there is a match, the index of the item in the vector
is returned by the function; if there is no match, it returns -1 to indicate
that no matching item was found.
*****************************************************************/
int searchItem(std::vector<items> dataset, std::string name) {
  std::cout << "Enter which you are searching for your purpose: ";
  std::cin >> name;
  for (int i = 0; i < dataset.size(); i++) {
    if (dataset[i].name == name) {
      return i;
    }
  }
  return -1;
}
/******************************************************************
The deleteItem() function has a representative vector and a string for the
product name to be deleted. At first, there is an integer called i, which is
equal to the searchItem function. If the searchFunction finds a match, the
deleteItem function uses erase() method to remove the item at the index returned
by the searchItem function. Otherwise, it only displays the "Product not found!"
message. 

References:
https://stackoverflow.com/a/5768334
******************************************************************/
std::vector<items> deleteItem(std::vector<items> dataset, std::string name) {
  int i = searchItem(dataset, name);
  if (i != -1) {
    dataset.erase(dataset.begin() + i);
    std::cout << "Item successfully deleted!" << std::endl;
  } else {
    std::cout << "Product not found!" << std::endl;
  }
  return dataset;
}
/****************************************************************************
The getDOE() function is a kind of error handling because, when the user wants
to edit an item's date, this function controls whether the user enters valid
inputs. For this function, a structure called 'date' is used to get inputs as
integers. At the end of this function (getDOE()), entered values are converted
to strings, and the function returns them.

references:
https://stackoverflow.com/a/26843934
****************************************************************************/
std::string getDOE() {
  date tmp;

  while (true) {
    std::cout << "Enter a day (1-31):";
    std::cin >> tmp.day;
    if (tmp.day > 0 && tmp.day <= 31) {
      break;
    } else {
      std::cout << "Invalid input! Try again." << std::endl;
    }
  }
  while (true) {
    std::cout << "Enter a month (1-12):";
    std::cin >> tmp.month;
    if (tmp.month > 0 && tmp.month <= 12) {
      break;
    } else {
      std::cout << "Invalid input! Try again." << std::endl;
    }
  }
  while (true) {
    std::cout << "Enter a year (2020-2025):";
    std::cin >> tmp.year;
    if (tmp.year >= 2020 && tmp.year <= 2025) {
      break;
    } else {
      std::cout << "Invalid input! Try again." << std::endl;
    }
  }
  return std::to_string(tmp.day) + "/" + std::to_string(tmp.month) + "/" +
         std::to_string(tmp.year);
}
/******************************************************************
The typeHandling() function is for cheking the user if they entered an
invalid type of product.
*******************************************************************/
std::string typeHandling(std::string type) {
  std::vector<std::string> types;
  types.push_back("Dairy");
  types.push_back("dairy");
  types.push_back("Snacks");
  types.push_back("snacks");
  types.push_back("Meat&Fish");
  types.push_back("meat&fish");
  types.push_back("Care-Product");
  types.push_back("care-product");
  types.push_back("Bread&spreads");
  types.push_back("bread&spreads");
  types.push_back("Freezer");
  types.push_back("freezer");
  types.push_back("Vegetables&fruit");
  types.push_back("vegetables&fruit");
  types.push_back("Dried-Goods");
  types.push_back("dried-goods");
  int flag = 0, supported = 0;

  while (!supported) {
    while (!flag) {
      for (auto elem : types) {
        if (type == elem) {
          flag = 1;
          supported = 1;
          break;
        }
      }
      break;
    }
    if (!flag) {
      std::cout << "It is not supported. Enter a different type:";
      std::cin >> type;
      supported = 0;
    }
  }
  return type;
}
/********************************************************************
The addItem() function allows the user to enter new information for each aspects
of the new item they want to add. It has a temporary items object called tmp and
asks the user to enter the name, DOE, quantity, price, and type of the new item.
The function holds new information and uses push_back() method to add it to the
vector. Finally, it retunes the dataset, and the new item is shown at the bottom
of the dataset.
********************************************************************/
std::vector<items> addItem(std::vector<items> dataset) {
  items tmp;
  std::cout << "Enter which item you would like to add:";
  std::cin >> tmp.name;
  std::cout << "Enter the date of experitation for your item like DD/MM/YYYY:";
  tmp.DOE_str = getDOE();
  std::cout << "Enter the information of quantity for your item:";
  std::cin >> tmp.quantity;
  std::cout << "Enter the information of price for your item:";
  std::cin >> tmp.price;
  std::cout << "Enter the information of type for your item:";
  std::cin >> tmp.type;
  std::cout << tmp.type << std::endl;
  tmp.type = typeHandling(tmp.type);

  dataset.push_back(tmp);
  return dataset;
}
/************************************************************************
The printItems() function displays all data from the data.txt file. It also has
the functionality of printing updated data (for example, when the user adds a
new item or edits an item). It can be seen that std::setw(n) was used to set the
field width. It is one of the parametric manipulators in the header of
<iomanip>. 

referances:
https://cplusplus.com/reference/iomanip/setw/
************************************************************************/
void printItems(std::vector<items> dataset) {
  std::cout << "PRODUCT\t\t"
            << "DATE\t\t"
            << "QUANTITY\t\t"
            << "PRICE\t\t"
            << "TYPE\n";
  for (int i = 0; i < dataset.size(); i++) {
    std::cout << std::setw(10) << std::left << dataset[i].name << " | ";
    std::cout << std::setw(0) << std::left << dataset[i].DOE_str << " | ";
    std::cout << std::setw(10) << std::left << dataset[i].quantity << "|";
    std::cout << std::setw(10) << std::left << dataset[i].price << " | ";
    std::cout << std::setw(10) << std::left << dataset[i].type << "\n";
  }
}
/**********************************************************************
The editItems() function allows the user to edit any aspect of existing data.
First of all, the function calls searchItem() function to find which item the
user is looking for. If the given input does not exist in the data.txt file, the
function displays an error message. If the given input is acceptable, the cycle
for editing any aspect of this item starts. Choosing an option 1 to 5, which is
provided with if/else if/else statements, in a 'while' loop to ask the user
again if they want to change another aspect. If they don't write the right
response, the cycle finishes, and then the user should choose the operation
"Edit an item" again. Inside the statements, it is required that the user enter
new information. When they enter new information, the code accesses the location
using dataset[itemindex]. and changes it. In the operation for editing DOE_str
getDOE() function is called to check if the entered inputs are correct or not.
**********************************************************************/
std::vector<items> editItem(std::vector<items> dataset) {
  std::string type;
  std::string name;
  int itemIndex = searchItem(dataset, name);

  if (itemIndex == -1) {
    std::cout << "Item not found." << std::endl;
    return dataset;
  }
  int option;
  std::string response;

  while (true) {
    std::cout << "Which attribute would you like to edit?" << std::endl;
    std::cout << "1. Name" << std::endl;
    std::cout << "2. Date of expiration (DOE)" << std::endl;
    std::cout << "3. Quantity" << std::endl;
    std::cout << "4. Price" << std::endl;
    std::cout << "5. Type" << std::endl;
    std::cout << "Select an option:";
    std::cin >> option;
    std::cout
        << "---------------------------------------------------------------"
        << std::endl;
    if (option == 1) {
      std::cout << "Enter the new name of the item: ";
      std::cin >> dataset[itemIndex].name;
    } else if (option == 2) {
      std::cout << "Enter the new DOE of the item (dd/mm/yyyy): ";
      dataset[itemIndex].DOE_str = getDOE();
    } else if (option == 3) {
      std::cout << "Enter the new quantity of the item: ";
      std::cin >> dataset[itemIndex].quantity;
    } else if (option == 4) {
      std::cout << "Enter the new price of the item: ";
      std::cin >> dataset[itemIndex].price;
    } else if (option == 5) {
      std::cout << "Enter the new type of the item: ";
      std::cin >> dataset[itemIndex].type;
      dataset[itemIndex].type = typeHandling(dataset[itemIndex].type);
    } else {
      std::cout << "Invalid option!" << std::endl;
    }

    std::cout << "Would you like to change another aspect (yes/no)?";
    std::cin >> response;

    if (response != "yes" && response != "YES" && response != "Yes") {
      break;
    }
  }
  return dataset;
}
/************************************************************************
The saveToField() function works by saving new actions to the file. Firstly,
DOE_str is defined to prevent the confusion between std::string DOE_str and date
DOE, because the date to be saved must be in string format. After that, the
function opens the file (it is defined as the filename) to write information in
the right index. At the end of the function, it closes the file. 
************************************************************************/
void saveToFile(std::vector<items> dataset, std::string filename) {
  int day, month, year;
  std::string DOE_str = std::to_string(day) + "/" + std::to_string(month) +
                        "/" + std::to_string(year);

  std::ofstream outfile(filename);
  for (int i = 0; i < dataset.size(); i++) // const auto &item : dataset
  {
    outfile << dataset[i].name << "  " << dataset[i].DOE_str << "  "
            << dataset[i].quantity << "  " << dataset[i].price << "  "
            << dataset[i].type << std::endl;
  }
  outfile.close();
}
/*************************************************************************
The ListAllData() function displays all data while reading the file named
data.txt. It opens the file via ifstream file(), and after that, variables are
defined. Then it reads the file, line by line. In this case, if the order of the
specified values is not the same in the folder, the error message displays. When
the function reads the data in the correct order, it adds them to the vector
(std::vector<item> &dataset) via push.back(). At the end, the function closes
the file and calls the printItems() function to print all the data. 
*************************************************************************/
void ListAllData(std::vector<items> &dataset, std::string filename) {
  std::ifstream file(filename);
  std::string line;

  int i = 0;

  std::string name, DOE_str, type, DOE;
  int day, month, year;
  int quantity;
  float price;

  while (getline(file, line)) {
    std::istringstream iss(line);
    if (!(iss >> name >> DOE_str >> quantity >> price >> type))
      throw std::runtime_error("Invalid data");

    iss >> name >> DOE_str >> quantity >> price >> type;

    dataset.push_back(items());
    dataset[i].name = name;
    dataset[i].DOE_str = DOE_str;
    dataset[i].quantity = quantity;
    dataset[i].price = price;
    dataset[i].type = type;

    i++;
  }
  file.close();

  printItems(dataset);
}
/************************************************************************
The printLowStockItems() function works by comparing the product's quantities
with a limit defined as an integer. A value for this integer is given in the
OtherAlternatives() function. When the user wants to display which items are low
on stock, this function accesses each data item in the data.txt file and then,
according to the index of data on quantity, compares limit and quantity. Lastly,
it stores the action in the vector, and it prints the information.
************************************************************************/
int printLowStockItems(std::vector<items> dataset, int limit) {
  std::cout << "Low in stock items: " << std::endl;
  for (int i = 0; i < dataset.size(); i++) // used to access each item
  {
    if (dataset[i].quantity <= limit) {
      std::cout << dataset[i].name << " (" << dataset[i].quantity << " left)"
                << std::endl;
    }
  }
  return 0;
}
/************************************************************************
The currentDate() function has the role of getting the current date. <time.h>
library is used in this function, and the function stores the current date in a
struct tm object. After that, it takes the day, month, and year values from this
object and combines them into an integer. Finally, it returns the current date
as an integer in the format of YYYYMMDD.

references:
https://stackoverflow.com/a/10467633
https://stackoverflow.com/a/19524766
https://stackoverflow.com/a/14580524
************************************************************************/
int currentDate() {
  time_t now = time(0);
  struct tm tstruct;
  tstruct = *localtime(&now);

  int day = tstruct.tm_mday;
  int month = tstruct.tm_mon + 1;
  int year = tstruct.tm_year + 1900;

  return year * 10000 + month * 100 + day;
}
/*****************************************************************
The convertDOEtoint() function has the responsibility of converting DOE_str,
which is in the format of a string, to an integer. It reads the input string and
stores the date information in a struct tm object using the strptime method.
After that, it takes the day, month, and year information from this object and
returns them in the YYYYMMDD format of an integer. If the DOE_str string is not
in the expected format, it returns -1.

references:
https://stackoverflow.com/a/19524766
https://stackoverflow.com/a/14580524
******************************************************************/
int convertDOEtoint(std::string DOE_str) {
    std::tm tm = {};
    std::istringstream ss(DOE_str);
    ss >> std::get_time(&tm, "%d/%m/%Y");

    if (ss.fail()) {
        return -1;
    }

    int d = tm.tm_mday;
    int m = tm.tm_mon + 1; // tm_mon is 0-based
    int y = tm.tm_year + 1900; // tm_year is years since 1900

    return y * 10000 + m * 100 + d;
}
// int convertDOEtoint(std::string DOE_str) {
//   struct tm tm {};
//   if (strptime(DOE_str.c_str(), "%m/%d/%Y", &tm)) {

//     int d = tm.tm_mday;
//     int m = tm.tm_mon + 1;
//     int y = tm.tm_year + 1900;

//     return y * 10000 + m * 100 + d;
//   }
//   return -1;
// }
/**********************************************************************
The printItemsExpire() function has a role in comparing the current date and the
products' dates. If the product's expiration date is lower than the current one,
it displays "[product's name]'s expiration date has passed.". If it isn't, the
function prints another message. the currentDate() function is called for the
current date and the convertDOEtoint() function is called for the products'
dates. Both functions equate to two different names in integer form. Lastly, the
function compares them in a 'if' statement.

references:
https://stackoverflow.com/questions/44475868/check-expiration-date-in-c11
https://stackoverflow.com/a/44478316
**********************************************************************/
int printItemsExpire(std::vector<items> dataset) {
  std::cout << "Items about to expire: " << std::endl;
  int today = currentDate();

  for (int i = 0; i < dataset.size(); i++) {
    std::string DOE_str = dataset[i].DOE_str;
    int productDate = convertDOEtoint(DOE_str);

    if (productDate < today) {
      std::cout << dataset[i].name << "'s expiration date has passed."
                << std::endl;
    }
  }
  std::cout
      << "Visit any of our branches to check out discounts on other products!"
      << std::endl;
  return 0;
}
/*********************************************************************
The searchByName() function works on allowing the use to enter product's name
what they are searching for.It defines and sets the boolean variable "found" to
false. A loop is created for each item in the dataset. If there is a match,
display the item(s) information and set the "found" variable to true. If there
is no match, error messages are printed.
*********************************************************************/
void searchByName(std::vector<items> dataset) {
  std::string itemN;
  std::cout << "Type the item's name: ";
  std::cin >> itemN;

  bool found = false;
  std::cout << "PRODUCT\t\t"
            << "DATE\t\t"
            << "QUANTITY\t\t"
            << "PRICE\t\t"
            << "TYPE\n";
  for (int i = 0; i < dataset.size(); i++) {
    if (dataset[i].name == itemN) {
      std::cout << std::setw(10) << std::left << dataset[i].name << " | ";
      std::cout << std::setw(0) << std::left << dataset[i].DOE_str << " | ";
      std::cout << std::setw(10) << std::left << dataset[i].quantity << " | ";
      std::cout << std::setw(10) << std::left << dataset[i].price << " | ";
      std::cout << std::setw(10) << std::left << dataset[i].type << std::endl;
      found = true;
    }
  }
  if (!found) {
    std::cout << "Item not found!" << std::endl;
  }
}
/*********************************************************************
The searchByNameORType() function allows the user to search for a product by
name or type. The function asks the user for a valid input (name or type) and
gets it via cin>>search. When they enter 'name', the function asks them to enter
which name they are looking for via calling the searchByName() function. There
is the same operation for 'type'. It declares a boolean variable "found" and
sets its value to false. A loop is created for each item in the dataset. If
there is a match, displays the details of the item(s) and returns the "found"
variable to true. If there is no match, it prints error messages.
*********************************************************************/
void searchByNameOrType(std::vector<items> dataset) {
  std::string name, type;
  std::string search;
  std::cout << "Search by name or type? Enter 'name' or 'type': ";
  std::cin >> search;

  if (search == "Type" || search == "type") {
    std::cout << "Specify the item's type: ";
    std::cin >> type;

    bool found = false;
    std::cout << "PRODUCT\t\t"
              << "DATE\t\t"
              << "QUANTITY\t\t"
              << "PRICE\t\t"
              << "TYPE\n";
    for (int i = 0; i < dataset.size(); i++) {

      if (dataset[i].type == type) {
        std::cout << std::setw(10) << std::left << dataset[i].name << " | ";
        std::cout << std::setw(0) << std::left << dataset[i].DOE_str << " | ";
        std::cout << std::setw(10) << std::left << dataset[i].quantity << " | ";
        std::cout << std::setw(10) << std::left << dataset[i].price << " | ";
        std::cout << std::setw(10) << std::left << dataset[i].type << std::endl;
        found = true;
      }
    }
    if (!found) {
      std::cout << "Item not available!" << std::endl;
    }
  } else {
    std::cout << "Invalid option!" << std::endl;
  }
  if (search == "Name" || search == "name") {
    searchByName(dataset);
  }
}
/*******************************************************************
The SaveandDisplay() function allows the user to only save their actions, only
display them, or do both. Their action choices are obtained via cin and then the
functions that are called (saveToFile() and printItems()) according to their
action choices do their jobs. For this situation, if-else if- else statements
are used. If the user does not enter a valid input, an error message is
displayed. 
********************************************************************/
void SaveandDisplay(std::vector<items> dataset) {
  std::string display, save;
  int action;
  std::string anyAspect;
  std::string filename =
      "data.txt"; // specify the filename to save the items to

  std::cout << "1. Save" << std::endl;
  std::cout << "2. Display" << std::endl;
  std::cout << "3. Save and Display" << std::endl;
  std::cout << "Do you want to save your action, print it, or do both?";
  std::cin >> action;
  std::cout << "NOTE: Unfortunately, if the product cannot be found in our "
               "data, so you cannot save or display it!"
            << std::endl;

  std::cout << "---------------------------------------------------------------"
            << std::endl;

  if (action == 1) {
    saveToFile(dataset, filename);
  } else if (action == 2) {
    printItems(dataset);
  } else if (action == 3) {
    saveToFile(dataset, filename);
    printItems(dataset);
  } else {
    std::cout << "Invalid option. Please try again!" << std::endl;
  }
}
/*****************************************************************
The OtherAlternatives() function asks users to enter some options, and these
options are built on switch-case statement. Do-while loop provides the user to
enter a valid input again if they choose invalid one. The printLowStockItems(),
printItemsExpire() and searchByNameOrType() are called inside of the options.
They do their own tasks according to the user's request.
*****************************************************************/
void OtherAlternatives(std::vector<items> dataset) {
  int choice;
  int limit = 5;
  do {
    std::cout
        << "---------------------------------------------------------------"
        << std::endl;
    std::cout << "YOUR ALTERNATIVES" << std::endl;
    std::cout << "1. Print low in stock items" << std::endl;
    std::cout << "2. Print items about to expire" << std::endl;
    std::cout << "3. Search for items by Name and Type" << std::endl;
    std::cout << "Search by the filtered property you want:";
    std::cin >> choice;
    std::cout
        << "---------------------------------------------------------------"
        << std::endl;
    switch (choice) {
    case 1:
      printLowStockItems(dataset, limit);
      break;
    case 2:
      printItemsExpire(dataset);
      break;
    case 3:
      searchByNameOrType(dataset);
      break;
    default:
      std::cout << "Please enter a valid option!" << std::endl;
      break;
    }
  } while ((choice != 1) && (choice != 2) && (choice != 3));
}
/**********************************************************************
The SelectOptions() function allows users to see the main menu, which contains
the main options. A switch-case statement is also utilised in this function to
allow users to choose an option that is shown in the main menu. Each of the
options calls SaveandDisplay() function to ask the user what they want to do
after selecting an option. Even if the user enters an invalid option, they will
see save or display sections, but when they try to do them, they will receive a
note that says it is impossible to do them. do-while loop checks if the user
entered a valid option and provides a question if they want to choose another
option. 

references:
https://www.w3schools.com/cpp/cpp_do_while_loop.asp
**********************************************************************/
void SelectOptions(std::vector<items> dataset) {
  int opt;
  std::string anyAspect;
  std::string answer;
  do {
    std::cout
        << "---------------------------------------------------------------"
        << std::endl;
    std::cout << std::setw(35) << std::right << "MAIN MENU" << std::endl;
    std::cout
        << "---------------------------------------------------------------"
        << std::endl;
    std::cout << "1. List all data" << std::endl;
    std::cout << "2. Add an item" << std::endl;
    std::cout << "3. Delete an item" << std::endl;
    std::cout << "4. Edit an item" << std::endl;
    std::cout << "5. Display the result for specific purposes " << std::endl;
    std::cout << "Select an option:";
    std::cin >> opt;
    std::cout
        << "---------------------------------------------------------------"
        << std::endl;

    switch (opt) {
    case 1:
      ListAllData(dataset, "data.txt");
      std::cout
          << "---------------------------------------------------------------"
          << std::endl;
      break;
    case 2:
      dataset = addItem(dataset);
      std::cout
          << "---------------------------------------------------------------"
          << std::endl;
      SaveandDisplay(dataset);
      break;
    case 3:
      dataset = deleteItem(dataset, anyAspect);
      std::cout
          << "---------------------------------------------------------------"
          << std::endl;
      SaveandDisplay(dataset);
      break;
    case 4:
      dataset = editItem(dataset);
      std::cout
          << "---------------------------------------------------------------"
          << std::endl;
      SaveandDisplay(dataset);
      break;
    case 5:
      OtherAlternatives(dataset);
      break;
    default:
      std::cout << "Please enter a valid option! " << std::endl;
      break;
    }
    std::cout
        << "-----------------------------------------------------------------"
        << std::endl;
    std::cout << "Would you want to select a different option (yes/no)?";
    std::cin >> answer;
  } while ((answer == "yes" || answer == "YES" || answer == "Yes"));
}
/**********************************************************************
It can be seen that this is the Finishing function to print the title
of the Supermarket System and call the function named SelectOptions
where the user can select an any option which they want to take a action.
***********************************************************************/
void Finishing(std::vector<items> dataset) {
  std::cout
      << "-----------------------------------------------------------------"
      << std::endl;
  std::cout << std::setw(40) << std::right << "SUPERMARKET SYSTEM" << std::endl;
  std::cout
      << "-----------------------------------------------------------------"
      << std::endl;
  SelectOptions(dataset);
}

int main() {
  std::vector<items> dataset; // declare a vector to hold the items
  Finishing(dataset);
  return 0;
}