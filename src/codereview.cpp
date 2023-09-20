// SPDX-FileCopyrightText: Copyright 2023 German Cancer Research Center (DKFZ) and contributors.
// SPDX-License-Identifier: MIT


#include <iostream>
#include <memory>
#include <string>
#include <vector>


/** \brief A basic bank account without any agreed overdraft.
 *
 * A bank account is owned by someone and has a balance.
 * Money can be deposited and withdrawn again.
 */
class Account
{
public:
  Account(std::string owner, double balance)
    : m_owner(owner),
      m_balance(balance)
  {
  }

  virtual ~Account() = default;

  virtual void deposit(double amount)
  {
    m_balance += amount;
  }

  virtual void withdraw(double amount)
  {
    m_balance -= amount;
  }

  /** \brief Print information about the account.
   */
  virtual void print()
  {
    std::cout << m_owner << '\n'
              << "  Balance : " << m_balance << '\n';
  }

  std::string getOwner()
  {
    return m_owner;
  }

  double getBalance()
  {
    return m_balance;
  }

protected:
  std::string m_owner;
  double m_balance;
};


/** \brief A less restrictive bank account with a custom agreed overdraft.
 *
 * The balance is not allowed to fall below the initially agreed overdraft.
 */
class CheckAccount : public Account
{
public:
  CheckAccount(std::string owner, double balance, double agreedOverdraft = -1000.0)
    : Account(owner, balance),
      m_agreedOverdraft(agreedOverdraft)
  {
  }

  ~CheckAccount() override = default;

  void withdraw(double amount) override
  {
    if (amount + m_agreedOverdraft < m_balance)
      m_balance -= amount;
  }

  void print() override
  {
    Account::print();
    std::cout << "  Agreed overdraft: " << m_agreedOverdraft << '\n';
  }

  double getAgreedOverdraft()
  {
    return m_agreedOverdraft;
  }

private:
  double m_agreedOverdraft;
};


/** \brief Load account data from the database.
 */
std::vector<std::shared_ptr<Account>> loadAccounts()
{
  // Create some mockup data for now instead of loading any real data from the database...

  std::vector<std::shared_ptr<Account>> accounts = {
    std::make_shared<CheckAccount>("Alice", 100.0),
    std::make_shared<CheckAccount>("Bob", 0.0, -500.0)
  };

  return accounts;
}


/** \brief Helper function to print information about all accounts.
 */
void printAccounts(const std::vector<std::shared_ptr<Account>>& accounts)
{
  for (size_t i = 0; i < accounts.size(); ++i)
    accounts[i]->print();
}


/** \brief Helper function to select an account by owner.
 */
Account* findAccount(std::vector<std::shared_ptr<Account>>& accounts, const std::string& owner)
{
  for (std::vector<std::shared_ptr<Account>>::const_iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
  {
    if ((*iter)->getOwner() == owner)
      return iter->get();
  }

  std::cerr << "Could not find " << owner << "'s account!\n";

  return nullptr;
}


/** \brief Withdraw money from a certain account.
 *
 * A wrapper function for the actual Account::withdraw() method to print some more information.
 */
void withdraw(Account account, double amount)
{
  std::cout << "Withdraw " << amount << " from " << account.getOwner() << "'s account...\n"
            << "  Balance before: " << account.getBalance() << '\n';

  account.withdraw(amount);

  std::cout << "  Balance after: " << account.getBalance() << '\n';
}


/** \brief A little showcase demonstrating our account API.
 *
 * Withdraw money from several accounts. We show that we can handle nonexistent accounts
 * and don't withdraw more money than allowed of course.
 */
int main()
{
  auto accounts = loadAccounts();

  printAccounts(accounts);

  auto* account = findAccount(accounts, "Alice");
  withdraw(*account, 1000.0);

  account = findAccount(accounts, "Bob");
  withdraw(*account, 1000.0);

  account = findAccount(accounts, "Mr. X");

  if (account != nullptr)
    withdraw(*account, 1.0);

  printAccounts(accounts);
}
