package com.example;

public class Main3 {
    public static void main(String[] args) throws InterruptedException {

        ResourcesExploiterWithLock resource = new ResourcesExploiterWithLock(0);
        ThreadedWorkerWithLock worker1 = new ThreadedWorkerWithLock(resource);
        ThreadedWorkerWithLock worker2 = new ThreadedWorkerWithLock(resource);
        ThreadedWorkerWithLock worker3 = new ThreadedWorkerWithLock(resource);

        worker1.start();
        worker2.start();
        worker3.start();

        worker1.join();
        worker2.join();
        worker3.join();



        System.out.println("Final rsc = " + resource.getRsc());
    }
}