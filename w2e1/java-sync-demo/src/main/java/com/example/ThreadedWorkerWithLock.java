package com.example;

public class ThreadedWorkerWithLock extends Thread {
    private final ResourcesExploiterWithLock rExp;

    public ThreadedWorkerWithLock(ResourcesExploiter resource) {
        this.rExp = (ResourcesExploiterWithLock) resource;
    }

    @Override
    public void run() {
        for (int i = 0; i < 1000; i++) {
            rExp.exploit();
        }
    }
}