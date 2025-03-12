#include "BackupSystem.h"

int main() {
    try {
        BackupJob* backupJob = new BackupJob();

        backupJob->setStorage("path/to/storage");

        BackupObject* obj1 = new BackupObject("path/to/file1.txt");
        BackupObject* obj2 = new BackupObject("path/to/file2.txt");

        backupJob->addBackupObject(obj1);
        backupJob->addBackupObject(obj2);// Установка алгоритма резервного копирования
        backupJob->setAlgorithm(new SingleStorage());
        backupJob->executeBackup(); // Выполнение резервного копирования

        backupJob->createRestorePoint(); // Создание точки восстановления

        // Смена алгоритма на раздельное хранилище
        backupJob->setAlgorithm(new SplitStorage());
        backupJob->executeBackup(); // Выполнение резервного копирования

        // Освобождение памяти
        delete backupJob; 

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}