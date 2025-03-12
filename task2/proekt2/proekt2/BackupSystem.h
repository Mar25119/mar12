#ifndef BACKUP_SYSTEM_H
#define BACKUP_SYSTEM_H

#include <iostream>
#include <vector>
#include <chrono>
#include <stdexcept>
#include <string>

// Класс объекта резервного копирования
class BackupObject {
public:
    explicit BackupObject(const std::string& path) : filePath(path) {}

    std::string getFilePath() const {
        return filePath;
    }

private:
    std::string filePath;
};

// Интерфейс для алгоритма резервного копирования
class BackupAlgorithm {
public:
    virtual void backup(const std::vector<BackupObject*>& objects, const std::string& storagePath) = 0;
    virtual ~BackupAlgorithm() = default;
};

// Реализация алгоритма общего хранилища
class SingleStorage : public BackupAlgorithm {
public:
    void backup(const std::vector<BackupObject*>& objects, const std::string& storagePath) override {
        std::cout << "Backing up to a single archive at: " << storagePath << std::endl;
        for (const auto& obj : objects) {
            std::cout << "Backing up file: " << obj->getFilePath() << std::endl;
        }
        // Реализация сохранения файлов
    }
};

// Реализация алгоритма раздельного хранения
class SplitStorage : public BackupAlgorithm {
public:
    void backup(const std::vector<BackupObject*>& objects, const std::string& storagePath) override {
        std::cout << "Backing up to individual archives at: " << storagePath << std::endl;
        for (const auto& obj : objects) {
            std::cout << "Backing up file: " << obj->getFilePath() << std::endl;
        }
    }
};

// Класс точки восстановления
class RestorePoint {
public:
    RestorePoint() : timestamp(std::chrono::system_clock::now()) {}

    void addBackupObject(BackupObject* obj) {
        backupObjects.push_back(obj);
    }

    void removeBackupObject(BackupObject* obj) {
        // Код для удаления объекта
    }

private:
    std::vector<BackupObject*> backupObjects;
    std::chrono::time_point<std::chrono::system_clock> timestamp;
};

// Класс джобы на резервное копирование
class BackupJob {
public:
    void addBackupObject(BackupObject* obj) {
        backupObjects.push_back(obj);
    }

    void removeBackupObject(BackupObject* obj) {
        // Код для удаления объекта
    }

    void createRestorePoint() {
        RestorePoint* point = new RestorePoint();
        for (auto& obj : backupObjects) {
            point->addBackupObject(obj);
        }
        restorePoints.push_back(point);
    }

    void setStorage(const std::string& path) {
        storagePath = path;
    }

    void setAlgorithm(BackupAlgorithm* algo) {
        algorithm = algo;
    }

    void executeBackup() {
        if (algorithm) {
            algorithm->backup(backupObjects, storagePath);
        }
        else {
            throw std::logic_error("Backup algorithm is not set!");
        }
    }

private:
    std::vector<BackupObject*> backupObjects;
    std::vector<RestorePoint*> restorePoints;
    std::string storagePath;
    BackupAlgorithm* algorithm = nullptr;
};

#endif 