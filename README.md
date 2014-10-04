dlib LIbrary
========================================================
  A C library for some personal convenient functions and components.

DSList
--------------------------------------------------------
  单链表相关库。
### 1) 声明一个链表头
    DSList * head

### 2) 初始化链表
    DSList * DSList_init ( void )
  例：<br />
  初始化上一步中的链表。

    head = DSList_init ();

### <a name="1-3"></a>3) 创建一个链表节点
    DSList * DSList_create_node ( void * data);
  该函数接收一个void类型的指针，该指针指向我们自己的需要插入到链表中的数据空间。<br />
  函数返回新创建节点的地址。

  例：<br />
  假设我们的数据存放在

    struct data {
        char    username[100];
        int     password;
    }

  创建一个节点，并将我们的数据放置其中。

    DSList * node = NULL;
    struct data * payload = (struct data *) malloc (sizeof (struct data));
    strcpy (payload->username, "Douglas");
    payload->password = 123456;
    node = DSList_create_node ((void *)payload);

### 4) 向链表尾部追加一个节点
    DSList * DSList_append (DSList * list, DSList * node);
  将<a href="#1-3">3) 创建一个链表节点</a>中创建的节点node添加到链表list尾部。<br />
  函数返回新的链表头。

  例：<br />
  我们将 node 节点插入到 head 的链表的最后面。

    head = DSList_append (head, node);

### 5) 向链表头部追加一个节点
    DSList * DSList_prepend (DSList *, DSList *);
  将<a href="#1-3">3) 创建一个链表节点</a>中创建的节点node添加到链表list的头部。<br />
  函数返回新的链表头。

  例：<br />
  我们将 node 节点插入到 head 的链表的最前面。

    head = DSList_prepend (head, node);

### 6) 将一个节点从链表中移除（该函数并不会释放该节点所占用的内存）
    DSList * DSList_remove (DSList * list, int func (void *), DSList ** node);
  将每个node中保存的数据作为参数传送给func函数，该函数根据传入的数据判断该节点是不是保存了需要的数据，如果是的话返回1，否则返回0。<br />
  该函数返回后会将node填充为移除的节点的地址，如果node为NULL的话，则忽略。<br />
  该函数不会释放node所占用的内存空间。<br />
  函数返回新的链表头。

  例：<br />
  我们将 node 节点从 head 链表中移除。<br />
  为了选出我们需要的节点，需要定义find函数。如果向该函数传入的数据满足条件则函数返回1，否则返回0。

    int find (void * payload) {
        struct data * py = (struct data *) payload;

        if (strcmp (py->username, "Douglas"))
            return 0;
        else
            return 1;
    }

  进行移除操作：

    head = DSList_remove (head, find, node);

### 7) 将一个节点从链表中删除（该函数释放节点所占内存）
    DSList * DSList_delete (DSList * list, int func (void *), void ** payload);
  将每个node中保存的数据作为参数传送给func函数，该函数根据传入的数据判断该节点是不是保存了需要的数据，如果是的话返回1，否则返回0。<br />
  该函数返回后会将payload填充为移除的节点中数据的地址，如果payload为NULL的话，则忽略。<br />
  函数返回新的链表头。

  例：<br />
  我们将 node 节点从 head 链表中删除。<br />
  为了选出我们需要的节点，需要定义find函数。如果向该函数传入的数据满足条件则函数返回1，否则返回0。

    int find (void * payload) {
        struct data * py = (struct data *) payload;

        if (strcmp (py->username, "Douglas"))
            return 0;
        else
            return 1;
    }

  进行删除操作：

    head = DSList_delete (head, find, node);

### 8) 对链表中的每一个元素都应用一个函数
    void DSList_traverse (DSList * list, int func (void *));
  将func函数应用到list中的每一个节点上。

  例：<br />
  对链表中的每个元素应用如下的打印函数。

    int print (void * payload) {
        struct data * py = (struct data *) payload;

        printf ("username = %s\n, password = %d\n", py->username, py->password);
    }

  使用该函数：

    DSList_traverse (head, print);

### 9) 搜索链表
    DSList * DSList_search (DSList * list, int func (void *));
  在链表list中搜索满足条件func的节点。<br />
  如果搜索到则返回节点地址，否则返回NULL。

  例：<br />
  将满足 find 函数的节点返回。<br />
  为了选出我们需要的节点，需要定义find函数。如果向该函数传入的数据满足条件则函数返回1，否则返回0。

    int find (void * payload) {
        struct data * py = (struct data *) payload;

        if (strcmp (py->username, "Douglas"))
            return 0;
        else
            return 1;
    }

  进行搜索操作：

    head = DSList_search (head, find, node);

### 10) 销毁节点
    void * DSList_destory_node (DSList *);
  释放node所占用的空间。<br />
  返回node中保存的数据的地址。

  例：<br />
  释放节点所占用的内存，并返回数据地址。

    data = DSList_destory_node (node);

### 11) 提取节点内数据
    void * DSList_strip (DSList *);
  提取node节点中的数据的指针。<br />
  返回node中保存数据的地址。

  例：<br />
  返回节点内所存数据的地址。

    data = DSList_strip (node);


常用函数库
--------------------------------------------------------
### 内存打印函数
    void DFprint_memory_default (void * start, int len);
  用十六进制打印以start开头的len个字节。

### 能够自定义的内存打印函数
    int DFprint_memory (void * start, char * format, int ele_per_line)；
  打印内存以start开始，每行打印ele_per_line个。<br />
  format制定需要打印的格式，该格式与GDB中x打印命令相同，但是不支持f，a，s，i打印类型。<br />

### 创建一个Socket服务器。
    int DFsocket_create_server (int type, const struct sockaddr * addr, socklen_t alen, int qlen);
  typer指定使用协议的协议族，例如AF_INET或者AF_UNIX。<br />
  addr为对应存放地址的结构体指针。<br />
  ale为addr结构体的有效长度。
  qlen为listen时的挂起队列长度。


END❡
====
