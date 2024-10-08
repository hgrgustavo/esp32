from sqlitecloud import connect


class Cloud:
    def __init__(self):
        super().__init__()
        self.connect = connect(
            "sqlitecloud://csqp1t5zhk.sqlite.cloud:8860/sqlite3.db?apikey=YeDoJjGUmfMJJ6PmfURHmPw0URdkyUGMmZCbCnrN76s")

        self.cursor = self.connect.cursor()
