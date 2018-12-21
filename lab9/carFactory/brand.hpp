#ifndef CS3_BRAND_HPP_
#define CS3_BRAND_HPP_

#include <vector>
#include <string>

using std::vector;
using std::string;

class Brand {
public:
  virtual ~Brand(); // makes class abstract
  string getName() const  {return brandName_;}
  vector<string> getModels() const  {return models_;}
  string getRandomModel() const;
  protected:
  Brand(string brandName, vector<string> models) : 
      brandName_(brandName),
      models_(models) {}

  string brandName_;
  vector<string> models_;
};


// two concrete products
class Ford : public Brand {
public:
  Ford() : Brand("Ford", 
                  { "Focus", "Mustang", "Explorer", "F-150", "F-250" }) {}
  virtual ~Ford() {}
};


class Toyota : public Brand {
public:
  Toyota() : Brand("Toyota",  
                  { "Corolla", "Camry", "Prius", "4Runner", "Yaris" }) {}
  virtual ~Toyota() {}
};

#endif // !CS3_BRAND_HPP_