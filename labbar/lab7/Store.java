public class Store {
    private Register registers[];
    private Queue done_Customers;


public Store(int amount_of_registers) {
    this.registers = new Register[amount_of_registers];
    this.done_Customers = new Queue();
    for (int i = 0; i < this.registers.length; i++) {
        this.registers[i] = new Register();
        this.registers[i].open();
    }
}

public String toString() {
    String result_string = ""; 
    for (Register r : this.registers) {
        result_string += r.toString() + "\n";
    }
    return result_string;
}

public int getAverageQueueLength() {
    int counter = 0;
    int counter_registers = 0;
    if (this.registers == null || this.registers.length == 0) {
        return 0;
    }
    for (Register r : this.registers) {
        counter += r.getQueueLength();
        counter_registers++; 
    }
    return counter/counter_registers; 
}

public void newCustomer(Customer c) {
    if (this.registers == null || this.registers.length == 0) {
        System.out.println("No registers exist");
    }
    else {
        int register_smallest_index = 0;
        int register_smallest_size = this.registers[0].getQueueLength();
        int index = 0;
        for (Register r : this.registers) {
            if(r.getQueueLength() <= register_smallest_size) {
                register_smallest_size = r.getQueueLength();
                register_smallest_index = index;
            }
            index++;
        }
        registers[register_smallest_index].addToQueue(c);
    }
}

public void step() {
    this.done_Customers = new Queue();
    
    if (this.registers == null) {
        System.out.println("No more registers to step through");
    }
    else {
        for (Register r : this.registers) {
            if (r.isOpen() && r.hasCustomers()) {
                r.step();
            }
            if (r.currentCustomerIsDone()) {
            Customer done_customer = r.removeCurrentCustomer();
            this.done_Customers.enqueue(done_customer);
            }
        }
    }
}

public boolean openNewRegister() {
    if (this.registers == null) {
        System.out.println("No registers to open");
        return false;
    }
    else {
        for (Register r : this.registers) {
            if (!r.isOpen() && r.getQueueLength() == 0) {
                r.open();
                return true;
            }
        }
        return false;
    }
}

public Queue getDoneCustomers() {
    return done_Customers;
}
}
