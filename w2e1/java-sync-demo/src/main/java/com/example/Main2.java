package com.example;

public class Main2 {
    public static void main(String[] args) throws InterruptedException {
        ResourcesExploiter resource = new ResourcesExploiter(0);
        
        ThreadedWorkerWithSync worker1 = new ThreadedWorkerWithSync(resource);
        ThreadedWorkerWithSync worker2 = new ThreadedWorkerWithSync(resource);
        ThreadedWorkerWithSync worker3 = new ThreadedWorkerWithSync(resource);


        worker1.start();
        worker2.start();
        worker3.start();

        worker1.join();
        worker2.join();
        worker3.join();



        System.out.println("Final rsc = " + resource.getRsc());
    }
}