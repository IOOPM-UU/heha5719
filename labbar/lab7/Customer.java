public class Customer {
    private int bornTime;
    private int groceries;


public Customer(int bornTime, int groceries) {
    this.bornTime = bornTime;
    this.groceries = groceries;
}

public String toString() {
    return "[" + this.groceries + "]";
}

public int serve() {
    if (this.groceries >= 1) {
    return this.groceries--;
    }
    else {
    System.out.println("No groceries left to remove");
    return 0;
    }
}

public int getBornTime() {
    return this.bornTime;
}

public boolean isDone() {
    if (this.groceries == 0) {
        return true;
    }
    else {
        return false;
    }
}

public static void main(String[] args) {
    Customer c = new Customer(0, 3);
    c.serve();
    c.serve();
    c.serve();
    if(c.isDone()) {
        System.out.println("The customer is done, just as expected!");
        } 
        else {
        System.out.println("The customer is not done, but should be...");
    }
}
}
