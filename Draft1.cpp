#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// structure creation
struct Product {
  string name;
  string expiry_date;
  int quantity;
  float price;
  string type;
};

// function to printout file
int printout() {

  // Open the text file
  ifstream infile("Draft1.txt");

  // Check if the file was successfully opened
  if (!infile) {
    cerr << "Error: unable to open file" << endl;
    return 1;
  }

  // Read all the lines from the file
  string line;
  vector<Product> products;

  while (getline(infile, line)) {

    // Split the line into a list of items
    stringstream ss(line);
    string item;
    vector<string> items;
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
    cout << p.name << " " << p.expiry_date << " " << p.quantity << " "
         << p.price << " " << p.type << endl;
  }

  return 0;
}

// delete empty lines
void delete_empty_line() {
  fstream file_stream;
  string current_read_line;

  file_stream.open("Draft1.txt", fstream::in | fstream::out | fstream::app);
  vector<string> lines;

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
  ofstream output_file("Draft1.txt");
  for (const string &line : lines) {
    output_file << line << '\n';
  }
  output_file.close();
}

bool isValidDate(const string& date) {
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


bool isValidFloat(const string& s, float& f) {
  std::istringstream iss(s);
  iss >> noskipws >> f; // noskipws considers leading whitespace invalid
  // Check the entire string was consumed and if either failbit or badbit is set
  return iss.eof() && !iss.fail(); 
} 


// insert function
int Insert() {

  // Create an instance of the Product struct
  Product product;

  // Prompt the user for the data to populate the struct
  cout << "Enter the product name: ";
  cin >> product.name;

  cout << "Enter the expiration date (dd/mm/yyyy): ";
  cin >> product.expiry_date;

  //if statment for product expiry date
  do{
  if (!isValidDate(product.expiry_date)) {
    cout << "Error: Invalid expiration date input the date again in the correct format (dd/mm/yyyy): " << endl;
    cin >> product.expiry_date;
  }
  } while (!isValidDate(product.expiry_date));
  
  cout << "Enter the quantity: ";
  char quantity[100];
  cin >> quantity;

do{
  if (isValidInt(quantity) == true){

    product.quantity = stoi(quantity);
  } else{

    cout << "Error: Invalid quantity input an integer: ";
    cin >> quantity;
  }
} while (isValidInt(quantity) == false);

  cout << "Enter the price: ";
  string price;
  cin >> price;

do{
    if (isValidFloat(price,product.price) == true){
      product.price = stof(price);
  }else{
    cout << "Error: Invalid price input a decimal number or an integer: ";
    cin >> price;
  }  
} while (isValidFloat(price,product.price) == false);


  cout << "Enter the type: ";
  cin >> product.type;
  cout << "\n\n";

  // Open the file in append mode
  ofstream file("Draft1.txt", ios::app);

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
    cout << "Error opening file" << endl;
  }

  printout();

  return 0;
}

// delete function
int Delete() {

  // Read the contents of the text file into a vector of Item objects
  vector<Product> items;
  ifstream file("Draft1.txt");
  string line;
  while (getline(file, line)) {
    Product item;
    istringstream iss(line);
    iss >> item.name >> item.expiry_date >> item.quantity >> item.price >>
        item.type;
    items.push_back(item);
  }
  file.close();

  // Iterate over the vector of Item objects and delete the desired item
  string name; // input provided by the user
  cout << "Write down the name of Item you want to delete: ";
  cin >> name;
  string type; // input provided by the user
  cout << "Write down the type of Item you want to delete: ";
  cin >> type;
  cout << "\n\n";

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
    cout << "The product with name '" << name << "' and type '" << type << "' was not found in the file.\n\n" << endl;
  }

  // Write the modified vector of Item objects back to the text file
  ofstream output_file("Draft1.txt");
  for (const Product &item : items) {
    output_file << item.name << '\t' << item.expiry_date << '\t'
                << item.quantity << '\t' << item.price << '\t' << item.type
                << '\n';
  }
  output_file.close();

  printout();

  return 0;
}

//Edit function
int Edit() {

  // Read the contents of the text file into a vector of Item objects
  vector<Product> items;
  ifstream file("Draft1.txt");
  string line;
  while (getline(file, line)) {
    Product item;
    istringstream iss(line);
    iss >> item.name >> item.expiry_date >> item.quantity >> item.price >>
        item.type;
    items.push_back(item);
  }
  file.close();

  // Iterate over the vector of Item objects and delete the desired item
  string name; // input provided by the user
  cout << "Write down the name of Item you want to edit: ";
  cin >> name;
  string type; // input provided by the user
  cout << "Write down the type of Item you want to edit: ";
  cin >> type;
  cout << "\n\n";

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
    cout << "The product with name '" << name << "' and type '" << type << "' was not found in the file." << endl << "add it as a new item: \n\n";
  }

  // Write the modified vector of Item objects back to the text file
  ofstream output_file("Draft1.txt");
  for (const Product &item : items) {
    output_file << item.name << '\t' << item.expiry_date << '\t'
                << item.quantity << '\t' << item.price << '\t' << item.type
                << '\n';
  }
  output_file.close();

 // Create an instance of the Product struct
  Product product;

  // Prompt the user for the data to populate the struct
  cout << "Enter the product name: ";
  cin >> product.name;

  cout << "Enter the expiration date (dd/mm/yyyy): ";
  cin >> product.expiry_date;

  //if statment for product expiry date
  do{
  if (!isValidDate(product.expiry_date)) {
    cout << "Error: Invalid expiration date input the date again in the correct format (dd/mm/yyyy): " << endl;
    cin >> product.expiry_date;
  }
  } while (!isValidDate(product.expiry_date));
  
  cout << "Enter the quantity: ";
  char quantity[100];
  cin >> quantity;

do{
  if (isValidInt(quantity) == true){

    product.quantity = stoi(quantity);
  } else{

    cout << "Error: Invalid quantity input an integer: ";
    cin >> quantity;
  }
} while (isValidInt(quantity) == false);

  cout << "Enter the price: ";
  string price;
  cin >> price;

do{
    if (isValidFloat(price,product.price) == true){
      product.price = stof(price);
  }else{
    cout << "Error: Invalid price input a decimal number or an integer: ";
    cin >> price;
  }  
} while (isValidFloat(price,product.price) == false);


  cout << "Enter the type: ";
  cin >> product.type;
  cout << "\n\n";

  // Open the file in append mode
  ofstream File("Draft1.txt", ios::app);

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
    cout << "Error opening file" << endl;
  }

  printout();

  return 0;
}

vector<string> split(const string &str) {
  vector<string> words;
  istringstream iss(str);
  string word;
  while (iss >> word) {
    words.push_back(word);
  }
  return words;
}

//Search Items function
int SearchItem(const string &name, const string &type) {

  // Open the text file in input mode
  ifstream file("Draft1.txt");

  bool item_found = false; // flag to track whether the item was found

  // Read the lines of the file one by one
  string line;
  while (getline(file, line)) {
    // Split the line into a vector of words
    vector<string> words = split(line);
    // Check if the name and type match the search query
    if (words[0] == name && words[4] == type) {
      item_found = true; // item was found
      // If the name and type match, print the line
      cout << line << endl;
    }
  }

  // If the item was not found, print a message to the user
  if (!item_found) {
    cout << "The item with name '" << name << "' and type '" << type << "' was not found in the file." << endl;
  }

  return 0;
}

//function for items about to expire
void items_about_to_expire() {

  // Open the text file and read its contents line by line
  ifstream file("Draft1.txt");
  string line;
  while (getline(file, line)) {
    // Split the line into fields using a stringstream
    stringstream ss(line);
    string name;
    string expirationDate;

    // Get the name and expiration date fields
    getline(ss, name, '\t');
    getline(ss, expirationDate, '\t');

    // Convert the expiration date string into a tm struct
    tm expiration{};
    istringstream expirationStream(expirationDate);
    expirationStream.imbue(locale("en_US.utf-8"));
    expirationStream >> get_time(&expiration, "%m/%d/%Y");

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
int items_low_in_stock(int threshold) {

  ifstream file("Draft1.txt");
  string line;

  // Read each line of the file
  while (getline(file, line)) {
    // Split the line into fields separated by tabs
    istringstream fields(line);
    Product item;

    // Read the fields from the line
    getline(fields, item.name, '\t');
    getline(fields, item.expiry_date, '\t');
    fields >> item.quantity;
    fields.ignore(1); // ignore the tab character
    fields >> item.price;
    fields.ignore(1); // ignore the tab character
    getline(fields, item.type);

    // Check if the quantity is below the threshold
    if (item.quantity < threshold) {
      cout << item.name << " has a low stock of " << item.quantity << endl;
    }
  }
  return 0;
}

int main() {

  printout();

    int functionNum;
    char functionNumChar[100];
  do{
    // printing out the menu
    cout
        << "\n\nUsing the following menu to function the database: "
           "\n1.Insert\n2.Delete\n3.Edit\n4.Search item\n5.Show items about to "
           "expire\n6.Show items low in stock\n7.Save and Quit\n\nInput the "
           "number of the "
           "function to proceed: ";

    // input function number
    cin >> functionNumChar;
    cout << "\n";

    // function if-statment
    if (isValidInt(functionNumChar) == true){

      functionNum = stoi(functionNumChar);

    if (functionNum == 1) {

      Insert();

    } else if (functionNum == 2) {

      Delete();

    } else if (functionNum == 3) {

      Edit();
    } else if (functionNum == 4) {

      // input name and type
      string name, type;
      cout << "Write down the name of the product you are looking for: ";
      cin >> name;
      cout << "Write down the type of the product you are looking for: ";
      cin >> type;
      cout << "\n\n";

      // running the function
      SearchItem(name, type);

    } else if (functionNum == 5) {

      items_about_to_expire();

    } else if (functionNum == 6) {

      // input the threshold
      int threshold;
      cout << "Write down the threshold of items to be considered low in stock: ";
      char thresholdchar [100];
      cin >> thresholdchar;
      
        do{
            if (isValidInt(thresholdchar) == false){
              cin.clear();
              cin.ignore();
              cout << "Error: invalid threshold please input an integer: ";
              cin >> thresholdchar;
            } else {

              threshold = stoi(thresholdchar);

            }
      } while (isValidInt(thresholdchar) == false);

      cout << "\n\n";
      // running the function
      items_low_in_stock(threshold);

    } else if (functionNum == 7) {

      exit(0);

    } else if (functionNum > 7) {

      cout << "Please Write down a number from 1-7 based of the menu printed below"<< endl;

    }
    } else {
      cout << "Please Write down a number from 1-7 based of the menu printed below"<< endl;
    }
  } while(isValidInt(functionNumChar) == false || true);

  return 0;
}