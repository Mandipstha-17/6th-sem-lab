const express = require('express');
const mysql = require('mysql2');
const path = require('path');

const app = express();
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

// MySQL Connection
const db = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: '',
  database: 'ecommerce'
});

db.connect(err => {
  if (err) console.error('DB error:', err);
  else console.log('MySQL Connected...');
});

// Save user details and order placed
app.post('/api/order', (req, res) => {
  const { name, email, password, phone, address, product, price } = req.body;

  // 1. Insert User Info
  const userSql = 'INSERT INTO users (name, email, password, phone, address) VALUES (?, ?, ?, ?, ?)';
  db.query(userSql, [name, email, password, phone, address], (err, userResult) => {
    if (err) return res.status(500).send(err);

    const userId = userResult.insertId;

    // 2. Insert Order Placed
    const orderSql = 'INSERT INTO orders (user_id, product_name, price) VALUES (?, ?, ?)';
    db.query(orderSql, [userId, product, price], (err) => {
      if (err) return res.status(500).send(err);
      res.send({ message: 'Order and user info saved successfully!' });
    });
  });
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));
