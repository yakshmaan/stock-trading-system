# stock-trading-system
# C Trading Platform

A complete stock trading system built in C with portfolio management, transaction tracking, and file persistence.

## Features

- **User System**: Registration, login, secure authentication
- **Trading**: Buy/sell stocks with real-time P/L calculations
- **Portfolio**: Track holdings, view current value, see profit/loss
- **Transaction History**: Complete log of all trades
- **Banking**: Deposit/withdraw funds
- **Admin Panel**: Add stocks, view all users
- **File Persistence**: All data saves automatically

**Default Admin:**
- Username: `admin`
- Password: `admin123`
- Balance: $1,000,000

**New Users:**
- Register to get $10,000 starting balance
- 8 stocks available to trade

## How It Works

### Data Structures
- **User**: Stores account info, balance, portfolio (max 50 stocks)
- **Stock**: Symbol, company name, current price
- **PortfolioItem**: Stock owned, quantity, average buy price
- **Transaction**: Complete trade history record

### Core Functions
- `buy_stock()`: Purchase shares, updates portfolio
- `sell_stock()`: Sell holdings, calculates P/L
- `view_portfolio()`: Shows all holdings with live values
- `save_data()`: Writes all data to file
- `load_data()`: Restores data on startup

### File Storage
All data saved to `trading_data.dat`:
- Users and credentials
- Portfolios and holdings
- Stock market data
- Transaction history

## Technical Details

**Language:** Pure C (no external libraries)  
**Lines:** ~900  
**Data Storage:** File I/O with text format  
**Memory:** Arrays and structures  
**Max Limits:** 100 users, 20 stocks, 500 transactions

### Key Algorithms
- **Average Price**: Calculates weighted average when buying same stock multiple times
- **P/L Calculation**: (Current Price - Avg Buy Price) × Quantity
- **Portfolio Search**: Linear search through holdings (O(n))

## Project Structure
```
trading.c
├── Structures (User, Stock, Portfolio, Transaction)
├── Global Arrays (users, stocks, transactions)
├── main() - Menu system and program flow
├── Authentication (register, login)
├── Trading (buy, sell, portfolio view)
├── Admin (add stocks, view users)
├── File I/O (save/load data)
└── Utilities (input validation, helpers)
```

## Example Usage

**1. Register and Login:**
```
Register → username: john, password: pass123
Login → Receive $10,000 balance
```

**2. Buy Stocks:**
```
View Stocks → Pick AAPL at $175.50
Buy 10 shares → Total: $1,755
Balance: $8,245
```

**3. Check Portfolio:**
```
Symbol: AAPL
Quantity: 10
Avg Price: $175.50
Current: $180.00
Value: $1,800
P/L: +$45.00 ✓
```

**4. Sell for Profit:**
```
Sell 10 AAPL at $180 → Receive $1,800
Profit: $45.00
Balance: $10,045
```

## Learning Outcomes

This project demonstrates:
- ✅ Complex data structures (nested structs, arrays)
- ✅ Pointer manipulation and memory management
- ✅ File I/O operations
- ✅ Algorithm design (search, calculate averages)
- ✅ Input validation and error handling
- ✅ Modular function design
- ✅ Real-world application logic

## Future Enhancements

- Random price fluctuations
- Stock search functionality
- Password change feature
- Export to CSV
- Date/time stamps
- Trading statistics

## License

Copyright (c) 2025 [yakshmaan]. All Rights Reserved.

This code is for portfolio demonstration. Viewing permitted, copying/using requires permission.

## Author
yaksh
email : yakshmaan6@gmail.com

