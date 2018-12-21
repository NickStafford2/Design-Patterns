// traversing genealogical tree using Composite and Visitors
// Mikhail Nesterenko 1/28/2015
// Nicholas Stafford. 5/ 1/2018
//

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

using std::cin;
using std::cout;
using std::endl;

///////////////////////////////////////////////////////////////////////////////
// Component
//
class Person {
public:
  Person(string firstName,
    Person* spouse,
    Person* father,
    Person* mother) :
    firstName_(firstName),
    spouse_(spouse),
    father_(father),
    mother_(mother) {}
  virtual void  accept(class PersonVisitor*) = 0;
  string        getFirstName() { return firstName_; }
  Person*       getSpouse() { return spouse_; }
  void          setSpouse(Person *spouse) { spouse_ = spouse; }
  Person*       getFather() { return father_; }
  Person*       getMother() { return mother_; }
  virtual       ~Person() {}
private:
  string        firstName_;
  Person*       spouse_;
  Person*       father_;
  Person*       mother_;
};

///////////////////////////////////////////////////////////////////////////////
// composites
// man has a last name 
class Man : public Person {
public:
  Man(string lastName,
    string firstName,
    Person* spouse,
    Person* father,
    Person* mother)
    : lastName_(lastName),
    Person(firstName,
      spouse,
      father,
      mother) {}
  string getLastName() { return lastName_; }
  void           accept(class PersonVisitor* visitor) override;
private:
  string lastName_;
};

// woman has a list of children
class Woman : public Person {
public:
  Woman(vector<Person *> children,
    string           firstName,
    Person*          spouse,
    Person*          father,
    Person*          mother)
    :
    children_(children),
    Person(firstName, spouse, father, mother) {}
  const vector<Person*>&
    getChildren() { return children_; }
  void               setChildren(const vector<Person *> &children)
  {
    children_ = children;
  }
  void               accept(class PersonVisitor *visitor) override;
private:
  vector<Person *>  children_;
};

// abstract visitor
class PersonVisitor {
public:
  virtual void visit(Man*) = 0;
  virtual void visit(Woman*) = 0;
  virtual      ~PersonVisitor() {}
};

// composite methods that define traversal
void Man::accept(PersonVisitor *visitor) {
  visitor->visit(this);
}

void Woman::accept(PersonVisitor *visitor) {
  // children traversal through mother only
  // father's children are not traversed so as not 
  // to traverse them twice: for mother and father
  visitor->visit(this);
  // traversing descendants
  for (auto child : children_)
    child->accept(visitor);
}

// concrete visitors
// the last name for a man is stored in object
// the last name a woman is determined by her 
// spouse if she is married
// or by her father if she is not
class NamePrinter : public PersonVisitor {
public:
  void visit(Man *m) override {
    cout << "-" << m->getFirstName() << " "
      << m->getLastName() << endl;
  }
  void visit(Woman *w) override {
    cout << "-" << w->getFirstName() << " ";
    if (w->getSpouse() != nullptr)
      cout << static_cast<Man *>(w->getSpouse())->getLastName();
    else if (w->getFather() != nullptr)
      cout << static_cast<Man *>(w->getFather())->getLastName();
    else
      cout << "Doe";
    cout << endl;
  }
};


class ChildrenPrinter : public PersonVisitor {
public:
  void visit(Man *m) override {
    cout << "-" << m->getFirstName() << ": ";
    Woman *spouse = static_cast<Woman *>
      (m->getSpouse());
    if (spouse != nullptr)
      printNames(spouse->getChildren());
    cout << endl;
  }
  void visit(Woman *w) override {
    cout << "-" << w->getFirstName() << ": ";
    printNames(w->getChildren());
    cout << endl;
  }
private:
  void printNames(const vector<Person *> &children) {
    for (const auto c : children)
      cout << c->getFirstName() << ", ";
  }
};

// part 1 
class MaidenNamePrinter : public PersonVisitor {
public:
  void visit(Man *m) override {
    /*cout << m->getFirstName() << " "
      << m->getLastName()
      << " has no Maiden Name" << endl;*/
  }
  void visit(Woman *w) override {
    cout << "- " << w->getFirstName() << " ";
    if (w->getFather() != nullptr)
      cout << static_cast<Man *>(w->getFather())->getLastName();
    else
      cout << "Doe";
    cout << endl;
  }
private:

};
///////////////////////////////////////////////////////////////////////////////
// prints out critical info for debugging
//
class DebugVisitor : public PersonVisitor {
public:
private:
};

///////////////////////////////////////////////////////////////////////////////
// finds a person in a tree
//
class FindPersonVisitor : public PersonVisitor {
public:
  FindPersonVisitor(string firstName, string lastName) :
    firstName_(firstName),
    lastName_(lastName),
    toFind(nullptr) {}

  void visit(Man *m) override {
    // must test if element you are visiting is the input
    if (m->getFirstName() == firstName_ && m->getLastName() == lastName_)
      toFind = m;
  }
  void visit(Woman *w) override {
    string tempLastName = "";
    if (w->getFirstName() == firstName_) {
      if (w->getSpouse() != nullptr)
        tempLastName = static_cast<Man*>(w->getSpouse())->getLastName();
      else if (w->getFather() != nullptr)
        tempLastName = static_cast<Man*>(w->getFather())->getLastName();
      else
        tempLastName = "Doe";
    }
    if (tempLastName == lastName_) {
      toFind = w;
    }
  }
  Person* getFound() { return toFind; }
private:
  const string firstName_;
  const string lastName_;
  Person* toFind;
};

///////////////////////////////////////////////////////////////////////////////
//Print whether it is possible for two individuals to marry. 
//The rules are as follows. 
//  It is illegal to marry 
//    oneself, 
//    one's siblings, 
//    parents, 
//    children and 
//    aunts/uncles. 
//  The gender of the person is not significant. 
//  It is also illegal to marry a person who is already married. 
//
class MarriageAdviseVisitor : public PersonVisitor {
public:
  MarriageAdviseVisitor(Person* a, Person* b) :
    a_(a),
    b_(b),
    canAMarryB_(false),
    canBMarryA_(false) {}

  void visit(Man *m) override {
    if (m == a_) {
      canAMarryB_ = setStatus(a_, b_);
    }
    if (m == b_) {
      canBMarryA_ = setStatus(b_, a_);
    }
    // called for each element in the tree
    // must test if element you are visiting is the input
  }
  void visit(Woman *w) override {
    if (w == a_) {
      canAMarryB_ = setStatus(a_, b_);
    }
    if (w == b_) {
      canBMarryA_ = setStatus(b_, a_);
    }
  }
  // use rules to create a list of people 
  // must create a function that tests if person is in list
  bool isCloselyRelated(Person* a, Person* b);

  bool canMarry() {
    return canBMarryA_ && canAMarryB_;
  }

private:
  bool setStatus(Person* a, Person* b);
  Person* a_;
  Person* b_;
  bool canAMarryB_;
  bool canBMarryA_;
  int state;
};

bool MarriageAdviseVisitor::setStatus(Person* a, Person* b) {
  return !isCloselyRelated(a, b) && !(a->getSpouse());
}


bool MarriageAdviseVisitor::isCloselyRelated(Person* a, Person* b) {
  if (a == nullptr) return true;
  if (b == nullptr) return true;
  // can not marry oneself
  if (a == b) return true;
  // can not marry ones sibling
  if (a->getFather() == b->getFather() && a->getFather() != nullptr)
    return true;
  if (a->getMother() == b->getMother() && a->getMother() != nullptr)
    return true;
  // check for aunts and uncles
  Woman* mother = static_cast<Woman*>(a->getMother());
  if (mother != nullptr) {
    if (mother->getMother() != nullptr) {
      Woman* grandMother = static_cast<Woman*>(mother->getMother());
      vector<Person*> auntsAndUncles = grandMother->getChildren();
      for (Person* temp : auntsAndUncles) {
        if (b == temp) return true;
      }
    }
  }
  return false; // not closely related
}

//  Your program should ask for two names and output whether they can marry. 
//  For example: 
//    Enter first candidate: Richard Moore
//    Enter second candidate: Carol Taylor
//    They can not marry.
//    
// demonstrating the operation
int main() {
  // setting up the genealogical tree      
  cout << " the tree is as follows                                                                    " << endl;
  cout << "                                                                                           " << endl;
  cout << "                                                                                           " << endl;
  cout << "    James Smith  <--spouse-->  Mary                                                        " << endl;
  cout << "                                |                                                          " << endl;
  cout << "                                |--------------------------------                          " << endl;
  cout << "                                |              |                |                          " << endl;
  cout << "                                |              |                |                          " << endl;
  cout << " William Johnson <--spouse-> Patricia      Robert Smith       Linda  <--spouse--> Bruce Lee" << endl;
  cout << "                                |                               |                          " << endl;
  cout << "                                |------------------             |-------------------       " << endl;
  cout << "                                |                 |             |                  |       " << endl;
  cout << "                                |                 |             |                  |       " << endl;
  cout << " Jennifer  <--spouse-->  Michael Johnson      Barbara        John Lee            Sarah     " << endl;
  cout << "     |                                                                                     " << endl;
  cout << "     |                                                                                     " << endl;
  cout << "     |                                                                                     " << endl;
  cout << "     |                                                                                     " << endl;
  cout << "   Susan                                                                                   " << endl;

  // first generation
  Man*    jamesSmith = new Man("Smith", "James", nullptr, nullptr, nullptr);
  Woman*  mary = new Woman({}, "Mary", nullptr, nullptr, nullptr);
  mary->setSpouse(jamesSmith);
  jamesSmith->setSpouse(mary);

  // second generation
  Woman*  patricia = new Woman({}, "Patricia", nullptr, jamesSmith, mary);
  Man*    williamJohnson = new Man("Johnson", "William", nullptr, nullptr, nullptr);
  patricia->setSpouse(williamJohnson);
  williamJohnson->setSpouse(patricia);

  Woman*  linda = new Woman({}, "Linda", nullptr, jamesSmith, mary);
  Man*    bruceLee = new Man("Lee", "Bruce", nullptr, nullptr, nullptr);
  linda   ->setSpouse(bruceLee);
  bruceLee->setSpouse(linda);


  vector<Person *> marysKids = {
    patricia,
    new Man("Smith",    "Robert",   nullptr, jamesSmith,      mary),
    linda
  };
  mary->setChildren(marysKids);

  // third generation
  Man*    michaelJohnson = new Man("Johnson", "Michael", nullptr, williamJohnson, patricia);
  vector<Person *> patsKids = {
    michaelJohnson,
    new Woman({},        "Barbara",   nullptr, williamJohnson,      patricia)
  };
  patricia->setChildren(patsKids);

  vector<Person *> lindasKids = {
    new Woman({},        "Sarah",   nullptr, bruceLee,      linda),
    new Man("Lee", "John", nullptr, bruceLee, linda)
  };
  linda->setChildren(lindasKids);


  Woman *jennifer = new Woman({}, "Jennifer", nullptr, nullptr, nullptr);
  vector<Person *> jensKids = {
    new Woman({},         "Susan",     nullptr, michaelJohnson,      jennifer)
  };




  jennifer      ->setSpouse(michaelJohnson);
  michaelJohnson->setSpouse(jennifer);
  jennifer      ->setChildren(jensKids);


  // defining two visitors
  ChildrenPrinter*   cp = new ChildrenPrinter;
  NamePrinter*       np = new NamePrinter;
  MaidenNamePrinter* mp = new MaidenNamePrinter;

  // executing the traversal with the composite
  // and the specific visitor

  cout << "\nONLY DECENDENTS OF MARY CAN BE VISITED DIRECTLY\n";
  
  cout << "\nNAME LIST\n";
  mary->accept(np);

  cout << "\nCHILDREN LIST\n";
  mary->accept(cp);

  cout << "\nMAIDEN NAME LIST (only women)\n";
  mary->accept(mp);

  cout << "\nMARIAGE ADVICE TEST\n";
  while (true) {
    cout << "Enter two candidites first and last names to test if they can marry"
         << endl;
    string p1FirstName, p1LastName, p2LastName, p2FirstName;
    cout << "  Enter first candidate:  ";
    cin >> p1FirstName;
    cin >> p1LastName;
    FindPersonVisitor* finder1 = new FindPersonVisitor(p1FirstName, p1LastName);
    mary->accept(finder1);
    Person* p1 = finder1->getFound();

    cout << "  Enter second candidate: ";
    cin >> p2FirstName;
    cin >> p2LastName;
    FindPersonVisitor* finder2 = new FindPersonVisitor(p2FirstName, p2LastName);
    mary->accept(finder2);
    Person* p2 = finder2->getFound();

    MarriageAdviseVisitor* mav = new MarriageAdviseVisitor(p1, p2);

    if (p1 == nullptr || p2 == nullptr) {
      cout << "  Who???" << endl;
      continue;
    }
    mary->accept(mav);

    if (mav->canMarry()) cout << "\nThese two can marry" << endl;
    else                 cout << "\nThese two can not marry" << endl;

    cout << "\n" << endl;
  }
  int i = 0;
}