#include <iostream>
#include <string>
#include <vector>
#include <memory>  // Для unique_ptr

using namespace std;

// Абстрактный класс устройств
class Device {
public:
    virtual void getName() const = 0;
    virtual void getInfo() const = 0;
    virtual string getNumber() const = 0;
    virtual ~Device() = default;  // Виртуальный деструктор

protected:
    string brand;
    int price;
    string nomenclatureNumber;
};

// Конкретные классы устройств
class Headphones : public Device {
private:
    string constructionType;
    string attachmentMethod;

public:
    Headphones(string brand, int price, string nomenclatureNumber, string constructionType, string attachmentMethod)
        : constructionType(constructionType), attachmentMethod(attachmentMethod) {
        this->brand = brand;
        this->price = price;
        this->nomenclatureNumber = nomenclatureNumber;
    }

    void getName() const override {
        cout << nomenclatureNumber << " " << brand << " " << price << endl;
    }

    void getInfo() const override {
        cout << brand << " " << price << " " << nomenclatureNumber << " "
             << constructionType << " " << attachmentMethod << endl;
    }

    string getNumber() const override {
        return nomenclatureNumber;
    }
};

class Microphones : public Device {
private:
    string frequencyRange;
    string sensitivity;

public:
    Microphones(string brand, int price, string nomenclatureNumber, string frequencyRange, string sensitivity)
        : frequencyRange(frequencyRange), sensitivity(sensitivity) {
        this->brand = brand;
        this->price = price;
        this->nomenclatureNumber = nomenclatureNumber;
    }

    void getName() const override {
        cout << nomenclatureNumber << " " << brand << " " << price << endl;
    }

    void getInfo() const override {
        cout << brand << " " << price << " " << nomenclatureNumber << " "
             << frequencyRange << "Hz " << sensitivity << "dB/w/m" << endl;
    }

    string getNumber() const override {
        return nomenclatureNumber;
    }
};

class Keyboards : public Device {
private:
    string switchType;
    string interfaceKeybord;

public:
    Keyboards(string brand, int price, string nomenclatureNumber, string switchType, string interfaceKeybord)
        : switchType(switchType), interfaceKeybord(interfaceKeybord) {
        this->brand = brand;
        this->price = price;
        this->nomenclatureNumber = nomenclatureNumber;
    }

    void getName() const override {
        cout << nomenclatureNumber << " " << brand << " " << price << endl;
    }

    void getInfo() const override {
        cout << brand << " " << price << " " << nomenclatureNumber << " "
             << switchType << " " << interfaceKeybord << endl;
    }

    string getNumber() const override {
        return nomenclatureNumber;
    }
};

// Интерфейс "фабрики" устройств
class DeviceFactory {
public:
    virtual unique_ptr<Device> createDevice(string brand, int price, string nomenclatureNumber, string param1, string param2) = 0;
    virtual ~DeviceFactory() = default;
};

// Конкретные классы "фабрики" устройств
class HeadphonesFactory : public DeviceFactory {
public:
    unique_ptr<Device> createDevice(string brand, int price, string nomenclatureNumber, string constructionType, string attachmentMethod) override {
        return make_unique<Headphones>(brand, price, nomenclatureNumber, constructionType, attachmentMethod);
    }
};

class MicrophonesFactory : public DeviceFactory {
public:
    unique_ptr<Device> createDevice(string brand, int price, string nomenclatureNumber, string frequencyRange, string sensitivity) override {
        return make_unique<Microphones>(brand, price, nomenclatureNumber, frequencyRange, sensitivity);
    }
};

class KeyboardsFactory : public DeviceFactory {
public:
    unique_ptr<Device> createDevice(string brand, int price, string nomenclatureNumber, string switchType, string interfaceKeybord) override {
        return make_unique<Keyboards>(brand, price, nomenclatureNumber, switchType, interfaceKeybord);
    }
};

int main() {
    vector<unique_ptr<Device>> devices;

    // Создание фабрик
    unique_ptr<DeviceFactory> headphonesFactory = make_unique<HeadphonesFactory>();
    unique_ptr<DeviceFactory> microphonesFactory = make_unique<MicrophonesFactory>();
    unique_ptr<DeviceFactory> keyboardsFactory = make_unique<KeyboardsFactory>();

    // Создание устройств с использованием фабрик
    devices.push_back(headphonesFactory->createDevice("Sony", 1500, "h1", "Вкладыши", "Дуговое крепление"));
    devices.push_back(headphonesFactory->createDevice("Marchall", 3000, "h2", "Накладные", "Дуговое крепление"));
    devices.push_back(microphonesFactory->createDevice("MicroSound", 980, "m1", "140-5000", "100"));
    devices.push_back(microphonesFactory->createDevice("Hiper", 5000, "m2", "20-20000", "105"));
    devices.push_back(keyboardsFactory->createDevice("Logitech", 1250, "k1", "Линейные переключатели", "USB"));
    devices.push_back(keyboardsFactory->createDevice("Razer", 3200, "k2", "Линейные переключатели", "USB + Bluetooth"));

    int choice;
    do {
        cout << "Выберите действие:" << endl;
        cout << "1. Вывести полный список устройств" << endl;
        cout << "2. Вывести информацию по устройству" << endl;
        cout << "3. Выйти" << endl << ">>> ";
        cin >> choice;

        string nomenclatureNumber;
        switch (choice) {
        case 1:
            for (const auto& item : devices) {
                item->getName();
            }
            break;

        case 2:
            cout << "Введите номенклатурный номер устройства: ";
            cin >> nomenclatureNumber;
            for (const auto& item : devices) {
                if (item->getNumber() == nomenclatureNumber) {
                    item->getInfo();
                    break;
                }
            }
            break;

        case 3:
            cout << "Выход" << endl;
            break;

        default:
            cout << "Некорректный выбор" << endl;
        }
    } while (choice != 3);

    return 0;
}