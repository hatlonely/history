# wget

wget -r -nH -c --cut-dirs=1 ftp://192.168.1.103:/pub/google/protobuf/protobuf-2.5.0
wget -r -nH -c --cut-dirs=1 ftp://192.168.1.103:/pub/google/gtest/gtest-1.6.0
wget -r -nH -c --cut-dirs=1 ftp://192.168.1.103:/pub/boost/boost-1.56.0

-r 递归下载目录
-nd 把下载的内容都加入当前目录，去掉目录结构
-nH 不创建以目标主机域名为目录名的目录
--cut-dirs=<number> 忽略远程目录中指定目录的目录层
-np 只下载指定目录及其子目录
-nc --no-clobber 不更改已经存在的文件
-o <log output file> 将日志写入指定文件中
-i --input-file=<download_file> 批量下载，把要下载的URL写在一个文件中
-O --output-document=<data output path> 将数据输出到该路径
-B --base=URL 使用-F和-i文件选项时，在相对链接前添加指定的URL
-x 与-nd相反，创建完整的目录结构
-l <number> 指定下载的层次
-m 读robots.txt，判断合适的参数来制作镜像站点
-c 断点续传
-t <times> 断点续传重试次数
-T <number of seconds> 超时等待时间，单位s
--reject=<type> 忽略某类文件
--accept=<type> 可以接受的文件类型
--http-user=<user> 设置http用户
--http-passwd=<passwd> 设置http用户密码
--proxy-user=<user> 设置代理用户
--proxy-passwd=<passwd> 设置代理密码
--proxy=<on/off> 使用或关闭代理
-Y <on/off> 使用或关闭代理
-b 后台运行
-w <number of seconds> 两次尝试之间的等待时间
- --quota=<size> 限制下载文件的总大小不能超过size，size的值如：2K, 3M, 1024等
-F --force-html 以html方式处输入文件
-P --directory-prefix=<path> 保存文件前先创建指定名称的目录

## 启动
-V, --version 显示 Wget 的版本并且退出。
-h, --help 打印此帮助。
-b, -background 启动后进入后台操作。
-e, -execute=COMMAND 运行‘.wgetrc’形式的命令。日志记录及输入文件：
-o, --output-file=文件 将日志消息写入到指定文件中。
-a, --append-output=文件 将日志消息追加到指定文件的末端。
-d, --debug 打印调试输出。
-q, --quiet 安静模式(不输出信息)。
-v, --verbose 详细输出模式(默认)。
-nv, --non-verbose 关闭详细输出模式，但不进入安静模式。
-i, --input-file=文件 下载从指定文件中找到的 URL。
-F, --force-html 以 HTML 方式处理输入文件。
-B, --base=URL 使用 -F -i 文件选项时，在相对链接前添加指定的 URL。

## 下载
-t, --tries=次数 配置重试次数（0 表示无限）。
--retry-connrefused 即使拒绝连接也重试。
-O --output-document=文件 将数据写入此文件中。
-nc, --no-clobber 不更改已经存在的文件，也不使用在文件名后添加 .#（# 为数字）的方法写入新的文件。
-c, --continue 继续接收已下载了一部分的文件。
--progress=方式 选择下载进度的表示方式。
-N, --timestamping 除非远程文件较新，否则不再取回。
-S, --server-response 显示服务器回应消息。
--spider 不下载任何数据。
-T, --timeout=秒数 配置读取数据的超时时间 (秒数)。
-w, --wait=秒数 接收不同文件之间等待的秒数。
--waitretry=秒数 在每次重试之间稍等一段时间 (由 1 秒至指定的 秒数不等)。
--random-wait 接收不同文件之间稍等一段时间(由 0 秒至 2*WAIT 秒不等)。
-Y, --proxy=on/off 打开或关闭代理服务器。
-Q, --quota=大小 配置接收数据的限额大小。
--bind-address=地址 使用本机的指定地址 (主机名称或 IP) 进行连接。
--limit-rate=速率 限制下载的速率。
--dns-cache=off 禁止查找存于高速缓存中的 DNS。
--restrict-file-names=OS 限制文件名中的字符为指定的 OS (操作系统) 所允许的字符。

## 目录
-nd --no-directories 不创建目录。
-x, --force-directories 强制创建目录。
-nH, --no-host-directories 不创建含有远程主机名称的目录。
-P, --directory-prefix=名称 保存文件前先创建指定名称的目录。
--cut-dirs=数目 忽略远程目录中指定数目的目录层。

## HTTP 选项
--http-user=用户 配置 http 用户名。
--http-passwd=密码 配置 http 用户密码。
-C, --cache=on/off (不)使用服务器中的高速缓存中的数据 (默认是使用的)。
-E, --html-extension 将所有 MIME 类型为 text/html 的文件都加上 .html 扩展文件名。
--ignore-length 忽略“Content-Length”文件头字段。
--header=字符串 在文件头中添加指定字符串。
--proxy-user=用户 配置代理服务器用户名。
--proxy-passwd=密码 配置代理服务器用户密码。
--referer=URL 在 HTTP 请求中包含“Referer：URL”头。
-s, --save-headers 将 HTTP 头存入文件。
-U, --user-agent=AGENT 标志为 AGENT 而不是 Wget/VERSION。
--no-http-keep-alive 禁用 HTTP keep-alive（持久性连接）。
--cookies=off 禁用 cookie。
--load-cookies=文件 会话开始前由指定文件载入 cookie。
--save-cookies=文件 会话结束后将 cookie 保存至指定文件。
--post-data=字符串 使用 POST 方法，发送指定字符串。
--post-file=文件 使用 POST 方法，发送指定文件中的内容。

## HTTPS (SSL) 选项
--sslcertfile=文件 可选的客户段端证书。
--sslcertkey=密钥文件 对此证书可选的“密钥文件”。
--egd-file=文件 EGD socket 文件名。
--sslcadir=目录 CA 散列表所在的目录。
--sslcafile=文件 包含 CA 的文件。
--sslcerttype=0/1 Client-Cert 类型 0=PEM (默认) / 1=ASN1 (DER)
--sslcheckcert=0/1 根据提供的 CA 检查服务器的证书
--sslprotocol=0-3 选择 SSL 协议；0=自动选择，
1=SSLv2 2=SSLv3 3=TLSv1

## FTP 选项
-nr, --dont-remove-listing 不删除“.listing”文件。
-g, --glob=on/off 设置是否展开有通配符的文件名。
--passive-ftp 使用“被动”传输模式。
--retr-symlinks 在递归模式中，下载链接所指示的文件(连至目录则例外）。

## 递归下载
-r, --recursive 递归下载。
-l, --level=数字 最大递归深度(inf 或 0 表示无限)。
--delete-after 删除下载后的文件。
-k, --convert-links 将绝对链接转换为相对链接。
-K, --backup-converted 转换文件 X 前先将其备份为 X.orig。
-m, --mirror 等效于 -r -N -l inf -nr 的选项。
-p, --page-requisites 下载所有显示完整网页所需的文件，例如图像。
--strict-comments 打开对 HTML 备注的严格(SGML)处理选项。

## 递归下载时有关接受/拒绝的选项
-A, --accept=列表 接受的文件样式列表，以逗号分隔。
-R, --reject=列表 排除的文件样式列表，以逗号分隔。
-D, --domains=列表 接受的域列表，以逗号分隔。
--exclude-domains=列表 排除的域列表，以逗号分隔。
--follow-ftp 跟随 HTML 文件中的 FTP 链接。
--follow-tags=列表 要跟随的 HTML 标记，以逗号分隔。
-G, --ignore-tags=列表 要忽略的 HTML 标记，以逗号分隔。
-H, --span-hosts 递归时可进入其它主机。
-L, --relative 只跟随相

