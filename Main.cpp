#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>


// structure creation
struct Product {
  std::string name;
  std::string expiry_date;
  int quantity;
  float price;
  std::string type;
};


int printout() {
/*
This function is used to printout the database on 
the screen it is usually used after every function.

inputs: none
outputs: Prints out the database
*/

  // Open the text file
  std::ifstream infile("Main.txt");

  // Check if the file was successfully opened
  if (!infile) {
    std::cerr << "Error: unable to open file" << std::endl;
    return 1;
  }

  // Read all the lines from the file
  std::string line;
  std::vector<Product> products;

  while (getline(infile, line)) {

    // Split the line into a list of items
    std::stringstream ss(line);
    std::string item;
    std::vector<std::string> items;
    while (getline(ss, item, '\t')) {
      items.push_back(item);
    }

    // Store the values in a struct and a vector
    Product product;
    product.name = items[0];
    product.expiry_date = items[1];
    product.quantity = stoi(items[2]);
    product.price = stof(items[3]);
    product.type = items[4];
    products.push_back(product);
  }

  // Close the file
  infile.close();

  // Print out the values from the structs in the vector
  for (const auto &p : products) {
    std::cout << p.name << " " << p.expiry_date << " " << p.quantity << " "
         << p.price << " " << p.type << std::endl;
  }

  return 0;
}


void delete_empty_line() {
/*
This function was made to handle the error after deleting an 
item it leaves an empty line which this function clears all the
empty lines in the file.

input: none
output: none
*/
  std::fstream file_stream;
  std::string current_read_line;

  file_stream.open("Main.txt", std::fstream::in | std::fstream::out | std::fstream::app);
  std::vector<std::string> lines;

  // Read all the lines until the end of the file
  while (getline(file_stream, current_read_line)) {
    // Check if the line is empty
    if (!current_read_line.empty()) {
      lines.push_back(current_read_line);
    }
  }

  file_stream.clear();
  file_stream.close();

  // Write the modified vector of strings back to the text file
  std::ofstream output_file("Main.txt");
  for (const std::string &line : lines) {
    output_file << line << '\n';
  }
  output_file.close();
}

bool isValidDate(const std::string& date) {
/*
This function was made to handle the date inputs,
so that the user does not input the wrong type into
all date related fields.

input: none
output: none
*/

  // check if the date is in the correct format (dd/mm/yyyy)
  if (date.length() != 10 || date[2] != '/' || date[5] != '/') {
    return false;
  }

  // extract the day, month, and year from the date
  int day = stoi(date.substr(0, 2));
  int month = stoi(date.substr(3, 2));
  int year = stoi(date.substr(6, 4));

  // check if the month is valid (1-12)
  if (month < 1 || month > 12) {
    return false;
  }

  // check if the day is valid for the given month
  if (day < 1 || day > 31) {
    return false;
  }
  if (month == 2) {
    // check if the day is valid for February
    if (day > 29) {
      return false;
    }
    if (day == 29) {
      // check if the year is a leap year
      if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)) {
        return false;
      }
    }
  } else if (month == 4 || month == 6 || month == 9 || month == 11) {
    // check if the day is valid for months with 30 days
    if (day > 30) {
      return false;
    }
  }

  return true;
}

bool isValidInt(char a[100]){
/*
This function was made to handle the integer inputs,
so that the user does not input the wrong type into
all integer related fields.

input: none
output: none
*/

   bool perfect = true;
    perfect = true;
     int len = strlen(a);
     
     for(int i = 0;i < len;i++){
        if(isdigit(a[i]) == 0){
            perfect = false;
            return false;
            break;
        }
     }

        if(perfect){
          
          return true;
          }
}


bool isValidFloat(const std::string& s, float& f) {
/*
This function was made to handle the decimal or float inputs,
so that the user does not input the wrong type into
all decimal or float related fields.

input: none
output: none
*/

  std::istringstream iss(s);
  iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
  // Check the entire string was consumed and if either failbit or badbit is set
  return iss.eof() && !iss.fail(); 
} // https://cplusplus.com/reference/ios/noskipws/



int Insert() {
/*
This function is made to insert items into the 
supermarket database(text file).

input: product name/product expiry date/product quantity/product price/product type
output: saves the inputs into the text file
*/

  // Create an instance of the Product struct
  Product product;

  // Prompt the user for the data to populate the struct
  std::cout << "Enter the product name: ";
  std::cin >> product.name;

  std::cout << "Enter the expiration date (dd/mm/yyyy): ";
  std::cin >> product.expiry_date;

  //if statement for product expiry date
  do{
  if (!isValidDate(product.expiry_date)) {
    std::cout << "Error: Invalid expiration date input the date again in the correct format (dd/mm/yyyy): " << std::endl;
    std::cin >> product.expiry_date;
  }
  } while (!isValidDate(product.expiry_date));
  
  std::cout << "Enter the quantity: ";
  char quantity[100];
  std::cin >> quantity;

do{
  if (isValidInt(quantity) == true){

    product.quantity = std::stoi(quantity);
  } else{

    std::cout << "Error: Invalid quantity input an integer: ";
    std::cin >> quantity;
  }
} while (isValidInt(quantity) == false);
  product.quantity = std::stoi(quantity);

  std::cout << "Enter the price: ";
  std::string price;
  std::cin >> price;

do{
    if (isValidFloat(price,product.price) == true){
      product.price = stof(price);
  }else{
    std::cout << "Error: Invalid price input a decimal number or an integer: ";
    std::cin >> price;
  }  
} while (isValidFloat(price,product.price) == false);


  std::cout << "Enter the type: ";
  std::cin >> product.type;
  std::cout << "\n\n";

  // Open the file in append mode
  std::ofstream file("Main.txt", std::ios::app);

  // Check if the file was opened successfully
  if (file.is_open()) {

    // Use the << operator to write the data to the file
    file << '\n'
         << product.name << "\t" << product.expiry_date << "\t"
         << product.quantity << "\t" << product.price << "\t" << product.type;

    // Close the file when you are finished writing
    file.close();

    // deletes empty lines
    delete_empty_line();

  } else {
    std::cout << "Error opening file" << std::endl;
  }

  printout();

  return 0;
}


int Delete() {
/*
This function is used to delete items
in the database (text file).

input: product name/product type
output: deletes an item from the text file
*/

  // Read the contents of the text file into a vector of Item objects
  std::vector<Product> items;
  std::ifstream file("Main.txt");
  std::string line;
  while (getline(file, line)) {
    Product item;
    std::istringstream iss(line);
    iss >> item.name >> item.expiry_date >> item.quantity >> item.price >>
        item.type;
    items.push_back(item);
  }
  file.close();

  // Iterate over the vector of Item objects and delete the desired item
  std::string name; // input provided by the user
  std::cout << "Write down the name of Item you want to delete: ";
  std::cin >> name;
  std::string type; // input provided by the user
  std::cout << "Write down the type of Item you want to delete: ";
  std::cin >> type;
  std::cout << "\n\n";

  bool product_found = false; // flag to track whether the product was found
  for (int i = 0; i < items.size(); i++) {
    if (items[i].name == name && items[i].type == type) {
      product_found = true; // product was found
      items.erase(items.begin() + i);
      break;
    }
  }

  // If the product was not found, print a message to the user
  if (!product_found) {
    std::cout << "The product with name '" << name << "' and type '" << type << "' was not found in the file.\n\n" << std::endl;
  }

  // Write the modified vector of Item objects back to the text file
  std::ofstream output_file("Main.txt");
  for (const Product &item : items) {
    output_file << item.name << '\t' << item.expiry_date << '\t'
                << item.quantity << '\t' << item.price << '\t' << item.type
                << '\n';
  }
  output_file.close();

  printout();

  return 0;
}


int Edit() {
/*
This function is used to edit an item that
already exists and changes the data.

input: product name/product type 
/product name/product expiration date/product quantity/product price/product type
output: changes an item in the text file
*/

  // Read the contents of the text file into a vector of Item objects
  std::vector<Product> items;
  std::ifstream file("Main.txt");
  std::string line;
  while (getline(file, line)) {
    Product item;
    std::istringstream iss(line);
    iss >> item.name >> item.expiry_date >> item.quantity >> item.price >>
        item.type;
    items.push_back(item);
  }
  file.close();

  // Iterate over the vector of Item objects and delete the desired item
  std::string name; // input provided by the user
  std::cout << "Write down the name of Item you want to edit: ";
  std::cin >> name;
  std::string type; // input provided by the user
  std::cout << "Write down the type of Item you want to edit: ";
  std::cin >> type;
  std::cout << "\n\n";

  bool product_found = false; // flag to track whether the product was found
  for (int i = 0; i < items.size(); i++) {
    if (items[i].name == name && items[i].type == type) {
      product_found = true; // product was found
      items.erase(items.begin() + i);
      break;
    }
  }

  // If the product was not found, print a message to the user
  if (!product_found) {
    std::cout << "The product with name '" << name << "' and type '" << type << "' was not found in the file." << std::endl << "add it as a new item: \n\n";
  }

  // Write the modified vector of Item objects back to the text file
  std::ofstream output_file("Main.txt");
  for (const Product &item : items) {
    output_file << item.name << '\t' << item.expiry_date << '\t'
                << item.quantity << '\t' << item.price << '\t' << item.type
                << '\n';
  }
  output_file.close();

 // Create an instance of the Product struct
  Product product;

  // Prompt the user for the data to populate the struct
  std::cout << "Enter the product name: ";
  std::cin >> product.name;

  std::cout << "Enter the expiration date (dd/mm/yyyy): ";
  std::cin >> product.expiry_date;

  //if statement for product expiry date
  do{
  if (!isValidDate(product.expiry_date)) {
    std::cout << "Error: Invalid expiration date input the date again in the correct format (dd/mm/yyyy): " << std::endl;
    std::cin >> product.expiry_date;
  }
  } while (!isValidDate(product.expiry_date));
  
  std::cout << "Enter the quantity: ";
  char quantity[100];
  std::cin >> quantity;

do{
  if (isValidInt(quantity) == true){

    product.quantity = std::stoi(quantity);
  } else{

    std::cout << "Error: Invalid quantity input an integer: ";
    std::cin >> quantity;
  }
} while (isValidInt(quantity) == false);
  product.quantity = std::stoi(quantity);

  std::cout << "Enter the price: ";
  std::string price;
  std::cin >> price;

do{
    if (isValidFloat(price,product.price) == true){
      product.price = std::stof(price);
  }else{
    std::cout << "Error: Invalid price input a decimal number or an integer: ";
    std::cin >> price;
  }  
} while (isValidFloat(price,product.price) == false);


  std::cout << "Enter the type: ";
  std::cin >> product.type;
  std::cout << "\n\n";

  // Open the file in append mode
  std::ofstream File("Main.txt", std::ios::app);

  // Check if the file was opened successfully
  if (File.is_open()) {

    // Use the << operator to write the data to the file
    File << '\n'
         << product.name << "\t" << product.expiry_date << "\t"
         << product.quantity << "\t" << product.price << "\t" << product.type;

    // Close the file when you are finished writing
    File.close();

    // deletes empty lines
    delete_empty_line();

  } else {
    std::cout << "Error opening file" << std::endl;
  }

  printout();

  return 0;
}

std::vector<std::string> split(const std::string &str) {
/*
this function is used to split the lines in word segments.

input: none
output: none
*/
  std::vector<std::string> words;
  std::istringstream iss(str);
  std::string word;
  while (iss >> word) {
    words.push_back(word);
  }
  return words;
}

//Search Items function
int SearchItem(const std::string &name, const std::string &type) {
/*
This function  is used to search for a specific
product in the database (text file).

input: product name/product type
output: prints out the item the product you are looking for
*/

  // Open the text file in input mode
  std::ifstream file("Main.txt");

  bool item_found = false; // flag to track whether the item was found

  // Read the lines of the file one by one
  std::string line;
  while (getline(file, line)) {
    // Split the line into a vector of words
    std::vector<std::string> words = split(line);
    // Check if the name and type match the search query
    if (words[0] == name && words[4] == type) {
      item_found = true; // item was found
      // If the name and type match, print the line
      std::cout << line << std::endl;
    }
  }

  // If the item was not found, print a message to the user
  if (!item_found) {
    std::cout << "The item with name '" << name << "' and type '" << type << "' was not found in the file." << std::endl;
  }

  return 0;
}


void items_about_to_expire() {
/*
This function is used to show the items that
are about to expire.

input: none
output: prints out the products about to expire
*/

  // Open the text file and read its contents line by line
  std::ifstream file("Main.txt");
  std::string line;
  while (getline(file, line)) {
    // Split the line into fields using a stringstream
    std::stringstream ss(line);
    std::string name;
    std::string expirationDate;

    // Get the name and expiration date fields
    getline(ss, name, '\t');
    getline(ss, expirationDate, '\t');

    // Convert the expiration date string into a tm struct
    tm expiration{};
    std::istringstream expirationStream(expirationDate);
    expirationStream.imbue(std::locale("en_US.utf-8"));
    expirationStream >> std::get_time(&expiration, "%m/%d/%Y");

    // Get the current date
    time_t currentTime = time(nullptr);
    tm currentDate = *localtime(&currentTime);

    // Calculate the number of days until the expiration date
    double daysUntilExpiration =
        difftime(mktime(&expiration), mktime(&currentDate)) / 86400;

    // If the item is about to expire (within 7 days), output its name and
    // expiration date
    if (daysUntilExpiration <= 7) {
      std::cout << name << " expires on " << expirationDate << std::endl;
    }
  }
}

//function for items low in stock
void items_low_in_stock(int threshold) {
/*
This function is used to show the items that
are low in stock.

input: threshold
output: prints out the products that are low in stock
*/

    std::ifstream file("Main.txt");
  std::string line;
  Product item;
  std::vector<Product> items_low_stock;

  while (getline(file, line)) {
    std::istringstream fields(line);
    getline(fields, item.name, '\t');
    getline(fields, item.expiry_date, '\t');
    fields >> item.quantity;
    fields.ignore(1);
    fields >> item.price;
    fields.ignore(1);
    getline(fields, item.type);

    if (item.quantity < threshold) {
      std::cout << item.name << " has a low stock of " << item.quantity << std::endl;
      items_low_stock.push_back(item);
    }
  }

  std::string answer;
  while (true) {
    std::cout << "Do you want to save the results in an external file (yes/no)?" << std::endl;
    std::cin >> answer;

    if (answer == "yes" || answer == "no") {
      break;
    } else {
      std::cout << "Invalid input. Please enter 'yes' or 'no'." << std::endl;
    }
  }

  if (answer == "yes") {
    std::string fileName;
    std::cout << "What do you want to name your file?" << std::endl;
    std::cin >> fileName;
    std::string fileNameText = fileName+".txt";
    std::ofstream InputFile(fileNameText);

    for (Product item : items_low_stock) {
      InputFile << item.name << "\t" << item.expiry_date << "\t" << item.quantity << "\t" << item.price << "\t" << item.type << std::endl;
    }

    std::cout << "Results saved in " << fileNameText << std::endl;
  }
}


int main() {

  printout();

    int functionNum;
    char functionNumChar[100];
  do{
    // printing out the menu
    std::cout
        << "\n\nUsing the following menu to function the database: "
           "\n1.Insert\n2.Delete\n3.Edit\n4.Search item\n5.Show items about to "
           "expire\n6.Show items low in stock\n7.Save and Quit\n\nInput the "
           "number of the "
           "function to proceed: ";

    // input function number
    std::cin >> functionNumChar;
    std::cout << "\n";

    // function if-statement
    if (isValidInt(functionNumChar) == true){

      functionNum = std::stoi(functionNumChar);

    if (functionNum == 1) {

      Insert();

    } else if (functionNum == 2) {

      Delete();

    } else if (functionNum == 3) {

      Edit();
    } else if (functionNum == 4) {

      // input name and type
      std::string name, type;
      std::cout << "Write down the name of the product you are looking for: ";
      std::cin >> name;
      std::cout << "Write down the type of the product you are looking for: ";
      std::cin >> type;
      std::cout << "\n\n";

      // running the function
      SearchItem(name, type);

    } else if (functionNum == 5) {

      items_about_to_expire();

    } else if (functionNum == 6) {

      // input the threshold
      int threshold;
      std::cout << "Write down the threshold of items to be considered low in stock: ";
      char thresholdchar [100];
      std::cin >> thresholdchar;
      
        do{
            if (isValidInt(thresholdchar) == false){
              std::cin.clear();
              std::cin.ignore();
              std::cout << "Error: invalid threshold please input an integer: ";
              std::cin >> thresholdchar;
            } else {

              threshold = std::stoi(thresholdchar);

            }
      } while (isValidInt(thresholdchar) == false);

      std::cout << "\n\n";
      // running the function
      items_low_in_stock(threshold);

    } else if (functionNum == 7) {

      exit(0);

    } else if (functionNum > 7) {

      std::cout << "Please Write down a number from 1-7 based of the menu printed below"<< std::endl;

    }
    } else {
      std::cout << "Please Write down a number from 1-7 based of the menu printed below"<< std::endl;
    }
  } while(isValidInt(functionNumChar) == false || true);

  return 0;
}