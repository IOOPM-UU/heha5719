public class Register {
    private boolean open;
    private Queue queue;

public Register() {
    Queue new_queue = new Queue();
    this.queue = new_queue;
}

public String toString() {
    if (!isOpen()) {
        return "X [ ]";
    }
    else {
        String follow_ups = "";
        for (int i = 1; i < getQueueLength(); i++) {
            follow_ups += "@";
        }
        if (getQueueLength() == 0) {
            return "[]";
        }
        Customer c = this.queue.first_customer();
        String first_person = c.toString();
        if (getQueueLength() == 1) {
            return first_person;
        }
        else {
            return first_person + follow_ups;
        }
    }
}

public void open() {
    this.open = true;
}

public void close() {
    this.open = false;
}

public boolean isOpen() {
    return this.open;
}

public boolean hasCustomers() {
    if (queue.length() > 0) {
        return true;
    }
    else {
        return false;
    }
}

public boolean currentCustomerIsDone() {
    if (this.getQueueLength() == 0) {
        return false;
    }
    return queue.first_customer().isDone();
}

public void addToQueue(Customer c) {
    queue.enqueue(c);
}

public Customer removeCurrentCustomer() {
    return queue.dequeue();
}

public int getQueueLength() {
    return queue.length();
}

public void step() {
    if (isOpen() && hasCustomers()) {
        queue.first_customer().serve();
    }
    else {
        System.out.println("Register is closed or queue is empty");
    }
}
}
