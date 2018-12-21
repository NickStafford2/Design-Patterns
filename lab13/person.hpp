#ifndef CS3_PERSON_HPP_
#define CS3_PERSON_HPP_


///////////////////////////////////////////////////////////////////////////////
// Component
//
class Person{ 
public:
                Person(string firstName, Person *spouse, 
                       Person *father, Person *mother)
                                        : firstName_(firstName), 
                                          spouse_   (spouse), 
                                          father_   (father), 
                                          mother_   (mother) {}
  virtual       ~Person()                 {}
  string        getFirstName()            {return firstName_;}
  Person*       getSpouse()               {return spouse_;}
  void          setSpouse(Person *spouse) {spouse_=spouse;}
  Person*       getFather()               {return father_;}
  virtual void accept(class PersonVisitor *)=0;  
private:
  string        firstName_;
  Person        *spouse_;
  Person        *father_;
  Person        *mother_;
};

///////////////////////////////////////////////////////////////////////////////
// composites
// man has a last name 
//
class Man: public Person{
public:
                Man(string lastName, string firstName, 
                    Person* spouse, 
                    Person* father, 
                    Person *mother)
                                        : lastName_(lastName), 
                                          Person(firstName, 
                                                 spouse, 
                                                 father, 
                                                 mother) {}
  string        getLastName()             {return lastName_;}
  void          accept(class PersonVisitor *visitor) override;
private:
  string        lastName_;
};

// woman has a list of children
class Woman: public Person {
public: 
                Woman(vector<Person *> children, 
                      string firstName, 
                      Person *spouse, 
                      Person *father, 
                      Person *mother)
                                        : children_(children),
                                          Person(firstName, 
                                                 spouse,
                                                 father, 
                                                 mother) {}
  const vector<Person *>& 
                getChildren()
                                          {return children_;}
  void          setChildren(const vector<Person *> &children)
                                          {children_ = children;}
  void          accept(class PersonVisitor *visitor) override;
private:
   vector<Person *> children_;
}; 


#endif