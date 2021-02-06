/* #include <iostream> */
/* #include <string> */
/* using namespace std; */

class Investment {
 public:
  Investment(string name, int price) : name_(name), price_(price) {}
  virtual ~Investment(){};

  virtual string name() const { return name_; }
  virtual string description() const = 0;
  virtual int purchasePrice() const { return price_; }
  virtual bool fungible() const { return false; }

 private:
  string name_;
  int price_;
};

class Painting : public Investment {
 public:
  Painting(string name, int price) : Investment(name, price) {}
  virtual ~Painting() {
    if (description() == "painting") {
      cout << "Destroying " << name() << ", a " << description() << endl;
    }
  }
  virtual string description() const { return "painting"; }
};

class Stock : public Investment {
 public:
  Stock(string name, int price, string symbol)
      : Investment(name, price), symbol_(symbol) {}
  virtual ~Stock() {
    cout << "Destroying " << name() << ", a stock holding" << endl;
  }
  virtual string description() const { return "stock trading as " + symbol_; }
  virtual bool fungible() const { return true; }

 private:
  string symbol_;
};

class House : public Investment {
 public:
  House(string name, int price) : Investment(name, price) {}
  virtual ~House() {
    cout << "Destroying the " << description() << " " << name() << endl;
  }
  virtual string description() const { return "house"; }
};

/* void display(const Investment *inv) { */
/*   cout << inv->name(); */
/*   if (inv->fungible()) cout << " (fungible)"; */
/*   cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() */
/*        << endl; */
/* } */

/* int main() { */
/*   Investment *portfolio[4]; */
/*   portfolio[0] = new Painting("Salvator Mundi", 450300000); */
/*   // Stock holdings have a name, value, and ticker symbol */
/*   portfolio[1] = new Stock("Lyft", 50000, "LYFT"); */
/*   portfolio[2] = new Stock("GameStop", 10000, "GME"); */
/*   portfolio[3] = new House("4 Privet Drive", 660000); */

/*   for (int k = 0; k < 4; k++) display(portfolio[k]); */

/*   // Clean up the investments before exiting */
/*   cout << "Cleaning up" << endl; */
/*   for (int k = 0; k < 4; k++) delete portfolio[k]; */
/* } */
