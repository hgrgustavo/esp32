from sqlitecloud import connect
from database import Database

class Cloud(Database):
    def __init__(self):
        super().__init__()
        self.connect = connect(
            "sqlitecloud://csqp1t5zhk.sqlite.cloud:8860?apikey=YeDoJjGUmfMJJ6PmfURHmPw0URdkyUGMmZCbCnrN76s")

