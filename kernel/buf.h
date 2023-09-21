struct buf {
  // 数据是否已经从磁盘读取到内存中
  int valid;   // has data been read from disk?
  // disk是否拥有最新的数据
  int disk;    // does disk "own" buf?
  // dev、blockno用来唯一标识一个磁盘块
  uint dev;
  uint blockno;
  // bread返回之前会申请该sleep lock，之后的操作会一直持有，最终会调用brelse释放
  struct sleeplock lock;
  // refcnt：记录使用当前buf的进程数，避免正在被使用的buf被清除
  // 0表示没有进程正在使用该buf；正数：现在有几个进程正在使用使用该buf（同一个时刻只有一个进程使用，其他进程会睡眠）
  uint refcnt;
  struct buf *prev; // LRU cache list
  struct buf *next;
  // 存放磁盘块中内容的数组
  uchar data[BSIZE];
};

