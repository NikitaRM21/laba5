#include <iostream>
#include <vector>
/*!
    \brief Класс интерфейса участника
    \author Никита Романов
    \version 1.0
    \date Май 2023 года

    Содержит метод уведомления о новой цене.
*/
using namespace std;
class Observer {
public:
  virtual void update(int price) = 0;
};

/*!
    \brief Класс аукционера
    \author Никита Романов
    \version 1.0
    \date Май 2023 года

    Содержит участников аукционера, текущую цену, методы добавления нового участника, установки новой цены и уведомления участников.
*/
class Subject {
  vector<Observer*> members;
public:
  int price = 0;
  void addMember(Observer *obs) {
    members.push_back(obs);
  }
  void setNewPrice(int value) {
    price = value;
    notify(value);
  }
  void notify(int price) {
    for (Observer *i: members) {
      i->update(price);
    }
  }
};

/*!
    \brief Класс участника аукциона
    \author Никита Романов
    \version 1.0
    \date Май 2023 года

    Содержит метод увеличения цены, и метод определяющий новую цену.
*/
class Member : public Observer {
  int price = 0;
public:
  Member(Subject *sub) {
    sub->addMember(this);
  }
  void raisePrice(Subject *sub,int value) {
    sub->setNewPrice(value);
  }
  void update(int price) override {
    this->price=price;
    cout << "I understand that new price is " << this->price << endl;
  }
};

int main() {
  for (int j=0; j<3; ++j) {
    Subject sub;
    int quantity;
    cout << "New auction started! Please, type a number of participants: ";
    cin >> quantity;
    vector<Member> auction;
    for (int i=0; i<quantity; ++i) {
       Member observer(&sub);
       auction.push_back(observer);
    }
    for (int k=0; k<quantity; ++k) {
      int newPrice;
      cout << "Please, type a new price or -1 to do nothing: ";
      cin >> newPrice;
      if (newPrice < sub.price) {
        cout << "Nonono, you little sly!" << endl;
        continue;
      }
      if (newPrice!=-1) {
        auction[k].raisePrice(&sub, newPrice);
      }
    }

  }
}
