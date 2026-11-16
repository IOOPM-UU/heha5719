import java.util.Random;

public class Simulation {
    Store store;
    int time;
    int intensity;
    int maxGroceries;
    int thresholdForNewRegister;

public Simulation(Store store, int time, int intensity, int maxGroceries, int thresholdForNewRegister) {
    this.store = store;
    this.time = time;
    this.intensity = intensity;
    this.maxGroceries = maxGroceries;
    this.thresholdForNewRegister = thresholdForNewRegister;
}

public String toString() {
    return store.toString() + " Time : " + time + " Average Waiting Time : " + AverageWaitingTime();
}

Random random = new Random();

public int AverageWaitingTime() {
    int total_Waiting_Time = 0;
    Queue queue_finished = store.getDoneCustomers();
    int length_of_finished = queue_finished.length();
    if (length_of_finished == 0) {
        return 0;
    }
    for (int i = 0; i < length_of_finished; i++) {
        Customer c = queue_finished.first_customer();
        total_Waiting_Time += this.time - c.getBornTime();
        queue_finished.dequeue();
    }
    return total_Waiting_Time/length_of_finished;
}

public void step() {
    store.step(); 
    int random_int = random.nextInt(100);
    if (random_int < this.intensity) {
        int amount_groceries = random.nextInt(maxGroceries) + 1;
        Customer c = new Customer(time, amount_groceries);
        store.newCustomer(c);
    }
    if (store.getAverageQueueLength() > thresholdForNewRegister) {
        store.openNewRegister();
    }
    time++;
}
}
