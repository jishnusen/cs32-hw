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
