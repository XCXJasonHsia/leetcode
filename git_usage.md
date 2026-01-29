# git使用手册
## github，或者说git server 端的操作：
+ github中增加用户public key的操作：
    + https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/
    + 注意不需要关注agent部分的操作，自己的电脑直接作为客户端访问github上的repository，没有必要通过agent。
    + 私钥放在自己电脑 linux 用户的home目录的 .ssh下
    ```bash
    [qixi@SHPQIXI-N .ssh]$ pwd
    /home/qixi/.ssh
    [qixi@SHPQIXI-N .ssh]$ ls -l
    total 44
    -r-------- 1 qixi qixi  419 Jan  2  2025 id_ed25519
    -r-------- 1 qixi qixi  105 Jan  2  2025 id_ed25519.pub
    ```
    + 注意私钥的权限是本人可读，用下面的命令设置：
    ```
    chmod 400 id_ed25519
    ```
## git特点：
+ 一定记住git有本地的repository和远端的repository的模型，每个开发者维护自己本地的repo，远端的repo是给所有开发者同步协调使用的。
+ git是整个代码库，也就是整个repository作为一个整体进行管理，不是分目录分文件管理的。整个代码库共享一个版本。使用git log会显示一个标签，这个标签就是git用来标记一个版本的数字签名, 譬如下面的 **commit 199ffd005730a4f12d01369fa7ac648340034bb4**
```
[qixi@SHPQIXI-N install]$ git remote -v
origin  ssh://git@bosenbbucket1.netscout.com:7999/~qixi/qixi-ran-deployment.git (fetch)
origin  ssh://git@bosenbbucket1.netscout.com:7999/~qixi/qixi-ran-deployment.git (push)
[qixi@SHPQIXI-N install]$ git log
commit e91adbe1c6d98633a652af0c8421c0c90243dc87 (HEAD -> my_code, origin/my_code)
Author: qifeng xia <qifeng.xia@foxmail.com>
Date:   Tue Sep 23 16:50:34 2025 +0800

    RAN-3372: A tool to check disk layout and VMs in hosts.ini
        Commit to dev branch.

commit c42d2c96b16f4c5065a71e8246516b9d25edbeb5 (tag: v6.4.2.506, tag: v6.4.2.505, tag: v6.4.2.504, tag: v6.4.2.503, master)                                                                                                                  
Merge: 199ffd00 fd7caf38
Author: Cheng, Ke <Ke.Cheng@netscout.com>
Date:   Mon Sep 22 05:14:33 2025 -0400

    Pull request #3664: RAN-3494:ransensor upgrade failed due to unchanged docker image ID

    Merge in RANI/ran-deployment from ~KCHENG2/ran-deployment:RAN-3494 to master

    * commit 'fd7caf38070a70322683572d22d39ee30fe24f5c':
      RAN-3494:ransensor upgrade failed due to unchanged docker image ID 1. remove unused docker image tag 2. prune dangling docker image

```
+ 在版本管理中，会引入branch， tag的概念，注意这写信息也会作为git repository的一部分，使用git pull命令后，远端repository的版本，tag信息都会同步到本地的repository。


## git基本命令
+ 查看git 版本和查看git 帮助文件：
    + git --version
    + git help:  这是git最权威的文档，要习惯查看git help。
+ 创建git repository
    + git init: 建立一个git 仓库，这个被github上的创建repository 按钮替代了，在git 客户端（个人电脑）可以不使用。
+ 在git客户端设置用户的信息，设置之后，在git上的每次提交，设置的用户信息都会被记录在log里
    + git config --global user.name  "Your Name"
    + git config --global user.email "your.email@example.com"
* 记住下面的常规操作：
    + git diff: 工作区中改动了一个文件，可以用来查看改动的内容，注意在使用git add之后就看不到了。
    + git add <文件路径和文件名>， 把当前的改动提交到缓冲区，注意要不能使用路径，一定要加具体文件名，支持使用通配符指定文件名。
    + git rm <文件路径和文件名>,  删除当前的文件，git add的相反操作。
    + git commit -am "I can not use vi so I use -am to add commit message"
        + 如果直接使用git commit，会出现vi，让你输入这次提交的comment，如果你不会使用vi，用 -am 参数，后面的引号里直接写提交参数。
        + 这个命令之后，当前的改动就直接提交到本地的repository里了。
    + git push origin: 本地repository中的内容推送到远端的git repository（git remote -v会显示远端repository的地址）
        + 注意经常使用这条命令推送到远端服务器，保持本地和远端同步。
    + git pull: 从远端的git repository把最新的信息同步到本地，这个在多人同步开发时候一定要经常做，保持多个开发者直接工作同步，及时解决冲突。
    + git log： 查看操作的提交记录。
    
    
## git branch
+ 下面这个命令是git branch 管理的关键，先放在这里你熟悉，以后等你理解git 的branch框架之后再写具体操作
```bash
[qixi@SHPQIXI-N install]$ git remote show origin
* remote origin
  Fetch URL: ssh://git@bosenbbucket1.netscout.com:7999/~qixi/qixi-ran-deployment.git
  Push  URL: ssh://git@bosenbbucket1.netscout.com:7999/~qixi/qixi-ran-deployment.git
  HEAD branch: master
  Remote branches:
    FT-5813              tracked
    RAN-3444             tracked
    coverage             tracked
    master               tracked
    my_code              tracked
    ran-deployment-6.3.1 tracked
    ran-deployment-6.3.2 tracked
    ran-deployment-6.3.3 tracked
    ran-deployment-6.3.4 tracked
    ran-deployment-6.3.5 tracked
    ran-deployment-6.4.0 tracked
    ran-deployment-6.4.1 tracked
  Local branches configured for 'git pull':
    FT-5813  merges with remote FT-5813
    coverage merges with remote coverage
    master   merges with remote master
    my_code  merges with remote my_code
  Local refs configured for 'git push':
    FT-5813  pushes to FT-5813  (up to date)
    coverage pushes to coverage (up to date)
    master   pushes to master   (local out of date)
    my_code  pushes to my_code  (up to date)

```
    