public class Queue {
    Node first;
    Node last;
    
private class Node {
    Customer element;
    Node next;

    Node(Customer element) {
        this.element = element;
        this.next = null;
    }
}

public class EmptyQueueException extends RuntimeException {
}

public Customer first_customer() {
    if (first == null) {
       throw new EmptyQueueException();
    }
    return first.element;
}

public int length() {
    int counter = 0;
    Node current = first;
    while (current != null) {
        current = current.next;
        counter++;
    }
    return counter;
}

public void enqueue(Customer c) {
    Node new_node = new Node(c);
    if (first == null) {
        first = new_node;
        last = new_node;
    }
    else {
        last.next = new_node;
        last = new_node;
    }
}

public Customer dequeue() {
    if (first == null) {
        throw new EmptyQueueException();
    }
    else if (first == last) {
        Customer tmp = first.element;
        first = null;
        last = null;
        return tmp;
    }
    else {
        Customer to_return = first.element;
        first = first.next;
        return to_return;
    }
}
}