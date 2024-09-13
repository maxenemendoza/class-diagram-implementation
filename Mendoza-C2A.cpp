#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

const int maxShoppingCart = 100; // maximum number of products in shopping cart 
const int maxOrders = 100; // maximum number of orders that can be made
const int productSize = 5; // number of products in product list 
const int idWidth = 15, nameWidth = 40, priceWidth = 25, quantityWidth = 10, totalPriceWidth = 20; // width for tables

void clearScreen(){ // function that clears screen 
    system("CLS");
}

void pauseScreen(){ // function that pauses screen 
    system("PAUSE");
}

class Product {
    private:
    int productID; 
    string productName; 
    double productPrice; 

    public:
    // function to get product id
    int getProductID() const{
        return productID;
    }

    // function to get product name
    string getProductName() const{
        return productName;
    }

    // function to get product price
    double getProductPrice() const{
        return productPrice;
    }

    // default constructor to initialize data members with specific value
    Product(): productID(0), productName(""), productPrice(0.0) {} // initialize data members with default value

    //  parameterized constructor to initialize data members with specific value
    Product(int id, string name, double price): 
        productID(id),
        productName(name),
        productPrice(price) {}

    // display all products in table format
    static void displayProductList(Product products[], int size){
        clearScreen();
        // table headers
        cout << left << setw(idWidth) << "Product ID" 
             << left << setw(nameWidth) << "Product Name" 
             << left << setw(priceWidth) << "Product Price (Php)" << endl;
        
        // separator line
        cout << left << setw(idWidth) << setfill('-') << ""
             << left << setw(nameWidth) << ""
             << left << setw(priceWidth-6) << "" << setfill(' ') << endl;
        
        // print details of each product in table
        for (int i=0; i<size; i++){
            cout << left << setw(idWidth) << products[i].productID 
                 << left << setw(nameWidth) << products[i].productName 
                 << left << setw(priceWidth) << fixed << setprecision(2) << products[i].productPrice << endl;
        }
    }

    void addToCart(class ShoppingCart& cart); // function that adds product to cart
};

class Order {
    private:
    Product orderProducts[maxShoppingCart]; // array that stores products from order
    int orderProductQuantity[maxShoppingCart]; // array to store quantities of the products
    int itemCount; // number of items in the order
    double totalPrice; // total price of the order
    int orderID; // unique order ID

    public:
    // parameterized constructor to initialize data members with specific value
        Order(Product products[], int quantities[], int count, double price, int id)
            : itemCount(count), totalPrice(price), orderID(id) {
                for (int i=0; i<count; i++) {
                    orderProducts[i] = products[i];
                    orderProductQuantity[i] = quantities[i];
                }
            }

    // default constructor to initialize data members with default value
    Order() : itemCount(0), totalPrice(0.0), orderID(0) {}

    void displayOrderForm() const{
        cout << "Order ID: " << orderID << endl;
        cout << "Total Amount: Php " << fixed << setprecision(2) << totalPrice << endl;
        cout << "Order Details: " << endl;

        // table headers
        cout << left << setw(idWidth) << "Product ID" 
             << left << setw(nameWidth) << "Product Name" 
             << left << setw(priceWidth) << "Product Price (Php)" 
             << left << setw(quantityWidth+6) << "Product Quantity" << endl;

        // separator line
        cout << left << setw(idWidth) << setfill('-') << ""
             << left << setw(nameWidth) << ""
             << left << setw(priceWidth) << "" 
             << left << setw(quantityWidth+6) << "" << setfill(' ') << endl;
            
        // display product details
        for (int i = 0; i < itemCount; i++) {
            double productTotal = orderProductQuantity[i] * orderProducts[i].getProductPrice();
            cout << left << setw(idWidth) << orderProducts[i].getProductID() 
                 << left << setw(nameWidth) << orderProducts[i].getProductName() 
                 << left << setw(priceWidth) << orderProducts[i].getProductPrice() 
                 << left << setw(quantityWidth) << orderProductQuantity[i] << endl;
            }
        cout << endl;
        pauseScreen();
        return;
    }
};

class ShoppingCart {
    private:
    Product cartProduct[maxShoppingCart]; // array that stores products in cart
    int cartProductQuantity[maxShoppingCart]; // array that stores quantity per product in cart
    int itemCount; // number of items in cart
    int orderID;
    Order orders[maxOrders]; // array that stores completed orders
    int orderCount; // number of orders

    public:
    // default constructor to initialize data members with default value
    ShoppingCart(): itemCount(0), orderID(1), orderCount (0) {} // initializes data members

    // add product and product quantity to cart
    void countProductCart(const Product& product, int quantity){ 
        if (itemCount < maxShoppingCart){
            cartProduct[itemCount] = product; // stores product in cart
            cartProductQuantity[itemCount] = quantity; // stores quantity of product in cart
            itemCount++; // increment move to next product
        }
        else {
            cout << "Shopping Cart is full!" << endl;
        }
    }

    // display all products in shopping cart in table format
    void displayShoppingCart() const{
        clearScreen();
        // table headers
        cout << left << setw(idWidth) << "Product ID" 
             << left << setw(nameWidth) << "Product Name" 
             << left << setw(priceWidth) << "Product Price (Php)" 
             << left << setw(quantityWidth) << "Product Quantity" << endl;
        
        // separator line
        cout << left << setw(idWidth) << setfill('-') << ""
             << left << setw(nameWidth) << ""
             << left << setw(priceWidth) << "" 
             << left << setw(quantityWidth+6) << "" << setfill(' ') << endl;
        
        // display product details
        for (int i=0; i<itemCount; i++){
            cout << left << setw(idWidth) << cartProduct[i].getProductID() 
                 << left << setw(nameWidth) << cartProduct[i].getProductName() 
                 << left << setw(priceWidth) << fixed << setprecision(2) << cartProduct[i].getProductPrice() 
                 << left << setw(quantityWidth) << cartProductQuantity[i]<< endl;
        }
    }
    
    void checkoutShoppingCart(){
        while (true){
            if (itemCount == 0){
                cout << endl;
                    cout << "Shopping Cart is empty!" << endl;
                    pauseScreen();
                    return;
                }
            else if (itemCount > 0 || itemCount < maxShoppingCart){
            char checkoutChoice;
            cout << endl;
            cout << "Do you want to check out all the products? (Y/N): ";
            cin >> checkoutChoice;
            clearScreen();

            switch (checkoutChoice){
                case 'Y':
                case 'y': { // display all the products that are for checkout and the total amount
                    double totalPrice = 0.0; // stores total price of all products in cart
                    // table headers
                    cout << left << setw(idWidth) << "Product ID" 
                        << left << setw(nameWidth) << "Product Name" 
                        << left << setw(priceWidth) << "Product Price (Php)" 
                        << left << setw(quantityWidth) << "Product Quantity" 
                        << left << setw(totalPriceWidth) << "Total Price (Php)" << endl;
            
                    // separator line
                    cout << left << setw(idWidth) << setfill('-') << ""
                        << left << setw(nameWidth) << ""
                        << left << setw(priceWidth) << "" 
                        << left << setw(quantityWidth) << "" 
                        << left << setw(totalPriceWidth) << "" << setfill(' ') << endl;

                    for (int i=0; i<itemCount; i++){
                        double productTotal = cartProductQuantity[i] * cartProduct[i].getProductPrice(); // calculate total price for each product
                        totalPrice += productTotal; // add total price of each product to total price of all products in cart

                        // display product details
                        cout << left << setw(idWidth) << cartProduct[i].getProductID() 
                            << left << setw(nameWidth) << cartProduct[i].getProductName() 
                            << left << setw(priceWidth) << cartProduct[i].getProductPrice() 
                            << left << setw(quantityWidth) << cartProductQuantity[i]
                            << left << setw(totalPriceWidth) << fixed << setprecision(2) << productTotal << endl;
                    }
                    cout << endl;
                    cout << "Total Price: Php " << fixed << setprecision(2) << totalPrice << endl; // display total price
                    
                    // store the order
                    if (orderCount < maxOrders) {
                        orders[orderCount] = Order(cartProduct, cartProductQuantity, itemCount, totalPrice, orderID);
                        orderCount++;
                        orderID++;
                        cout << "You have successfully checked out the products!" << endl;
                    } else {
                        cout << "You have reached the order limit!" << endl;
                    }
                    
                    itemCount = 0; // reset cart
                    pauseScreen();
                    return; // exit loop and return to menu
                }

                case 'N':
                case 'n':
                    return; // exit loop and return to menu

                default:
                    cout << "Invalid input. Try again!" << endl;
                    return; // exit loop and return to menu
            }
                }
        }
    }
    void displayAllOrders() const {
        if (orderCount == 0){
            clearScreen();
            cout << "You have placed 0 orders!" << endl;
            pauseScreen();
            clearScreen();
            return;
        }
        clearScreen();
        cout << "All Orders:" << endl;
        for (int i = 0; i < orderCount; i++) {
            orders[i].displayOrderForm(); // display each order
        }
}
};

char addChoice; // user choice whether to add another product to shopping cart

void Product::addToCart(ShoppingCart& cart){
    int productQuantity;
    cout << "Enter the quantity: ";
    cin >> productQuantity;

    cart.countProductCart(*this, productQuantity); // add product to cart
    cout << "Product added successfully!" << endl;
    }

int main (){
    int menuChoice;

    // className arrayName[arraySize]
    Product products[productSize] = { // array that stores product list

        // Product (productID, productName, productPrice)
        Product(1, "Cadbury Dairy Milk Chocolate Bar", 159.00),
        Product(2, "Hershey's Kisses Milk Chocolate", 325.00),
        Product(3, "Milka Strawberry Milk Chocolate", 89.00),
        Product(4, "Mars Minis Chocolate Bars", 269.00),
        Product(5, "Galaxy Milk Chocolatey Moments", 119.00)
    };
    
    ShoppingCart cart; // create object
    
    while (true){
        clearScreen();
    	cout << "Welcome to Maxene's Chocolate Factory!" << endl;
    	cout << "Menu" << endl;
    	cout << "1 - View Products" << endl;
    	cout << "2 - View Shopping Cart" << endl;
    	cout << "3 - View Orders" << endl;
    	cout << "4 - Exit" << endl;

   	 	cout << "Enter choice: ";
   	 	cin >> menuChoice;
        cout << endl;

    	switch(menuChoice){
        	case 1: { // view products
            Product::displayProductList(products, productSize); // display product list
                
            while (true){
            int productID; // stores selected product 
                cout << endl;
                cout << "Enter the Product ID to add to cart: ";
                cin >> productID;

                if (productID >= 1 && productID <= productSize) {
                    products[productID - 1].addToCart(cart); // add selected product to cart
                } else {
                    cout << "Invalid Product ID!" << endl;
                }
        
            char addChoice; // allows user to add another product to cart
            cout << endl;
            cout << "Would you like to add another product? (Y/N): ";
            cin >> addChoice; 

            if (addChoice == 'N' || addChoice == 'n') {
                break; // exit loop and return to menu
            }
        }
        break;
}
            case 2: // view shopping cart
            cart.displayShoppingCart(); // display shopping cart
            cart.checkoutShoppingCart(); // allow user to checkout cart
            break;

            case 3: // view orders
                cart.displayAllOrders(); // display all stored orders
                break;
            
            case 4: // exit
                cout << "Thank you for purchasing from Maxene's Chocolate Factory!" << endl;
                return 0; // exit program

        	default: // invalid input
        	cout << "Invalid input. Try again!" << endl;
            pauseScreen();
            break;
    	}
	}
}