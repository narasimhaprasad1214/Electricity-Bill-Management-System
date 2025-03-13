#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Customer {
    int meter_number;
    char name[50];
    char address[100];
    char connection_type[20]; 
    struct Customer* next;
} Customer;

typedef struct Bill {
    int meter_number;
    int units;
    float amount_due;
    char due_date[20];
    char status[10]; 
    struct Bill* next;
} Bill;

typedef struct Payment {
    int meter_number;
    float amount_paid;
    char payment_date[20];
    struct Payment* next;
} Payment;

typedef struct Complaint {
    int meter_number;
    char issue[100];
    char status[15]; 
    struct Complaint* next;
} Complaint;

// Global pointers
Customer* customerHead = NULL;
Bill* billHead = NULL;
Payment* paymentHead = NULL;
Complaint* complaintHead = NULL;

// Function to display menu
void displayMenu() {
    printf("\n=====================================\n");
    printf("     ELECTRICITY BILLING SYSTEM     \n");
    printf("=====================================\n");
    printf("1.  Add Customer\n2.  Display Customers\n");
    printf("3.  Generate Bill\n4.  Display Bills\n");
    printf("5.  Make Payment\n6.  Display Payments\n");
    printf("7.  Register Complaint\n8.  Resolve Complaint\n");
    printf("9.  Display Complaints\n10. Exit\n");
    printf("=====================================\n");
}


int getValidChoice() {
    int choice;
    while (1) {
        printf("\nEnter your choice: ");
        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 10) return choice;
        else {
            printf("Invalid input! Enter a number between 1-10.\n");
            while (getchar() != '\n');
        }
    }
}


void addCustomer() {
    Customer* newCustomer = (Customer*)malloc(sizeof(Customer));

    printf("\nEnter Meter Number: ");
    scanf("%d", &newCustomer->meter_number);

    printf("Enter Name: ");
    scanf(" %[^\n]", newCustomer->name);

    printf("Enter Address: ");
    scanf(" %[^\n]", newCustomer->address);

    printf("Enter Connection Type (Domestic/Commercial/Industrial): ");
    scanf("%s", newCustomer->connection_type);

    newCustomer->next = customerHead;
    customerHead = newCustomer;
    printf("Customer added successfully!\n");
}


void displayCustomers() {
    if (!customerHead) {
        printf("No customers found!\n");
        return;
    }

    printf("\nCustomer List:\n");
    printf("Meter No  | Name       | Address        | Connection Type\n");
    printf("------------------------------------------------------------\n");

    Customer* temp = customerHead;
    while (temp) {
        printf("%-10d | %-10s | %-15s | %-10s\n", temp->meter_number, temp->name, temp->address, temp->connection_type);
        temp = temp->next;
    }
}

void generateBill() {
    int meterNum, units;
    float rate, amount;

    printf("\nEnter Meter Number: ");
    scanf("%d", &meterNum);

    Customer* customer = customerHead;
    while (customer && customer->meter_number != meterNum) customer = customer->next;
    if (!customer) {
        printf("Customer not found!\n");
        return;
    }

    printf("Enter Units Consumed: ");
    scanf("%d", &units);

    if (strcmp(customer->connection_type, "Domestic") == 0) rate = 3.5;
    else if (strcmp(customer->connection_type, "Commercial") == 0) rate = 5.0;
    else rate = 6.5;

    amount = units * rate;

    Bill* newBill = (Bill*)malloc(sizeof(Bill));
    newBill->meter_number = meterNum;
    newBill->units = units;
    newBill->amount_due = amount;
    strcpy(newBill->due_date, "10th Next Month");
    strcpy(newBill->status, "Pending");
    newBill->next = billHead;
    billHead = newBill;

    printf("Bill Generated: %d units, Total: %.2f\n", units, amount);
}


void displayBills() {
    if (!billHead) {
        printf("No bills found!\n");
        return;
    }

    printf("\nBill List:\n");
    printf("Meter No | Units | Amount Due | Due Date    | Status\n");
    printf("------------------------------------------------------\n");

    Bill* temp = billHead;
    while (temp) {
        printf("%-8d | %-5d | %-10.2f | %-10s | %-10s\n", temp->meter_number, temp->units, temp->amount_due, temp->due_date, temp->status);
        temp = temp->next;
    }
}

void makePayment() {
    int meterNum;
    float amount;

    printf("\nEnter Meter Number: ");
    scanf("%d", &meterNum);

    Bill* bill = billHead;
    while (bill && bill->meter_number != meterNum) bill = bill->next;
    if (!bill || strcmp(bill->status, "Paid") == 0) {
        printf("No pending bill found!\n");
        return;
    }

    printf("Enter Payment Amount: ");
    scanf("%f", &amount);

    bill->amount_due -= amount;
    if (bill->amount_due <= 0) strcpy(bill->status, "Paid");

    printf("Payment successful! Remaining due: %.2f\n", bill->amount_due);
}

void registerComplaint() {
    Complaint* newComplaint = (Complaint*)malloc(sizeof(Complaint));

    printf("\nEnter Meter Number: ");
    scanf("%d", &newComplaint->meter_number);
    
    printf("Describe Issue: ");
    scanf(" %[^\n]", newComplaint->issue);

    strcpy(newComplaint->status, "Pending");
    newComplaint->next = complaintHead;
    complaintHead = newComplaint;

    printf("Complaint registered successfully!\n");
}


void resolveComplaint() {
    int meterNum;
    printf("\nEnter Meter Number: ");
    scanf("%d", &meterNum);

    Complaint* complaint = complaintHead;
    while (complaint && complaint->meter_number != meterNum) complaint = complaint->next;
    if (!complaint || strcmp(complaint->status, "Resolved") == 0) {
        printf("No unresolved complaint found!\n");
        return;
    }

    strcpy(complaint->status, "Resolved");
    printf("Complaint resolved successfully!\n");
}

void displayComplaints() {
    if (!complaintHead) {
        printf("No complaints found!\n");
        return;
    }

    printf("\nComplaint List:\n");
    printf("Meter No | Issue                           | Status\n");
    printf("------------------------------------------------------\n");

    Complaint* temp = complaintHead;
    while (temp) {
        printf("%-8d | %-30s | %-10s\n", temp->meter_number, temp->issue, temp->status);
        temp = temp->next;
    }
}

int main() {
    while (1) {
        displayMenu();
        switch (getValidChoice()) {
            case 1: addCustomer(); break;
            case 2: displayCustomers(); break;
            case 3: generateBill(); break;
            case 4: displayBills(); break;
            case 5: makePayment(); break;
            case 6: printf("Payment History Not Implemented Yet!\n"); break;
            case 7: registerComplaint(); break;
            case 8: resolveComplaint(); break;
            case 9: displayComplaints(); break;
            case 10: exit(0);
        }
    }
    return 0;
}