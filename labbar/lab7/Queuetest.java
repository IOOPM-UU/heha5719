public class Queuetest {
    public static void main(String[] args) {
    Queue queue = new Queue();

    Customer c1 = new Customer(0, 3);
    Customer c2 = new Customer(3, 1);
    Customer c3 = new Customer(7, 5);

    queue.enqueue(c1);
    queue.enqueue(c2);
    queue.enqueue(c3);

    System.out.println(queue.dequeue() == c1);
    System.out.println(queue.dequeue() == c2);
    System.out.println(queue.dequeue() == c3);
    }
}
