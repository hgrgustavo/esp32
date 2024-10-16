from sqlite3 import connect


class Database:
    def __init__(self):
        self.connection = connect("sqlite3.db")
        self.cursor = self.connection.cursor()

        self.cursor.execute("""
        CREATE TABLE IF NOT EXISTS data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            distance TEXT
        );        
        """)
        self.connection.commit()
