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

// 1. Signup Form API
app.post('/api/signup', (req, res) => {
  const { name, email, password } = req.body;
  const sql = 'INSERT INTO users (name, email, password) VALUES (?, ?, ?)';
  db.query(sql, [name, email, password], (err) => {
    if (err) return res.status(500).send({ error: 'Signup failed' });
    res.send({ message: 'User registered successfully!' });
  });
});

// 2. Login Page API
app.post('/api/login', (req, res) => {
  const { email, password } = req.body;
  const sql = 'SELECT * FROM users WHERE email = ? AND password = ?';
  db.query(sql, [email, password], (err, results) => {
    if (err || results.length === 0) {
      return res.status(401).send({ error: 'Invalid email or password' });
    }
    res.send({ message: 'Login successful!', user: results[0] });
  });
});

// 3. Save Order Placed into Database
app.post('/api/order', (req, res) => {
  const { userId, product, price } = req.body;
  const sql = 'INSERT INTO orders (user_id, product_name, price) VALUES (?, ?, ?)';
  db.query(sql, [userId, product, price], (err) => {
    if (err) return res.status(500).send({ error: 'Order failed' });
    res.send({ message: 'Order placed successfully!' });
  });
});

app.listen(3000, () => console.log('Server running on http://localhost:3000'));
