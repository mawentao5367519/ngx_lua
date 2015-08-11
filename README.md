# ngx_lua
nginx + lua + C++

环境配置:

推荐OpenResty安装

安装步骤可以参考http://openresty.org/#Installation。

1.安装依赖,我的是centos,其他系统请参考上边链接里的说明
  yum install readline-devel pcre-devel openssl-devel gcc
2.下载 openresty (可以下载最新的)
  wget http://openresty.org/download/ngx_openresty-1.7.7.2.tar.gz  
  tar -xzvf ngx_openresty-1.7.7.2.tar.gz
  ngx_openresty-1.7.7.2/bundle目录里存放着nginx核心和很多第三方模块，比如有我们需要的Lua和LuaJIT。
3.安装LuaJIT
  cd bundle/LuaJIT-2.1-20150120/  
  make clean && make && make install  
  ln -sf luajit-2.1.0-alpha /usr/local/bin/luajit 
4.下载ngx_cache_purge模块，该模块用于清理nginx缓存
  在bundle目录下
  wget https://github.com/FRiCKLE/ngx_cache_purge/archive/2.3.tar.gz  
  tar -xvf 2.3.tar.gz  
5.下载nginx_upstream_check_module模块，该模块用于ustream健康检查
  在bundle目录下
  wget https://github.com/yaoweibin/nginx_upstream_check_module/archive/v0.3.0.tar.gz  
  tar -xvf v0.3.0.tar.gz  
6.安装ngx_openresty
  在ngx_openresty-1.7.7.2目录下
  修改configure
  约452行
  my $opts_line = ' --user=www --group=www --with-http_stub_status_module  --with-http_gzip_static_module --with-ipv6 ';
  ./configure --prefix=/usr/local --with-http_realip_module  --with-pcre  --with-luajit --add-module=./bundle/ngx_cache_purge-2.3/ --add-module=./bundle/nginx_upstream_check_module-0.3.0/ -j2  
  make && make install

会生成以下目录
      /usr/loca/luajit/           #luajit环境，luajit类似于java的jit，即即时编译，lua是一种解释语言，通过luajit可以即时编译lua代码到机器代码，得到很好的性能；
      /usr/loca/lualib/           #要使用的lua库，里边提供了一些默认的lua库，如redis，json库等，也可以把一些自己开发的或第三方的放在这；
      /usr/loca/nginx/            #安装的nginx；通过/usr/servers/nginx/sbin/nginx  -V 查看nginx版本和安装的模块
环境配置完成
7.启动nginx
  /usr/loca/nginx/sbin/nginx
8.
  编辑nginx.conf配置文件
  vim /usr/loca/nginx/conf/nginx.conf  
  在http部分添加如下配置 (可选)
  #lua模块路径，多个之间”;”分隔，其中”;;”表示默认搜索路径，默认到/usr/servers/nginx下找  
  lua_package_path "/usr/servers/lualib/?.lua;;";  #lua 模块  
  lua_package_cpath "/usr/servers/lualib/?.so;;";  #c模块 
  
  创建一个server
  server {  
    listen       80;  
    server_name  _;  
  
    location /lua {  
        default_type 'text/html';  
        lua_code_cache off;  
        content_by_lua_file /usr/example/lua/test.lua;  
    }  
  }  
  
  /usr/example/lua/test.lua
  ngx.say("Hello World")
  
  快打开浏览器看看吧
  
      
