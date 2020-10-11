# markdown

<!-- tag: markdown, tool -->

## 语法

    #       h1标题
    ##      h2标题
    ###     h3标题
    >       层次
    >>      层次
    *       无序列表
    -       无序列表
    +       无序列表
    1.      有序列表
    2.      有序列表
    ***     分割线
    -----   分割线
    *强调*
    _强调_
    **加粗**
    ***加粗和强调***
    `代码`
    ``代码段``
    ```代码块```
    4个缩进或者1个制表符表示代码块
    \ 转义

    [link](http://url.net) 链接
    ![img](path) 图片
    [link][id] 链接
    <http://google.com/> 自动链接

    [id]: http://example.com/ 'option title here'
    [id]: http://example.com/ "option title here"
    [id]: http://example.com/ (option title here)

## 拓展语法

    | First Header  | Second Header |
    | ------------- | ------------- |
    | Content Cell  | Content Cell  |
    | Content Cell  | Content Cell  |

## 参考

- [markdown语法介绍](http://wowubuntu.com/markdown/)
- [markdown python支持](https://github.com/trentm/python-markdown2)
- [markdown javascript支持](https://github.com/chjj/marked)
- [markdown 拓展语法](https://github.com/trentm/python-markdown2/wiki/Extras)
- [markdown 表格支持](https://help.github.com/articles/github-flavored-markdown/#tables)
- [markdownPad](http://markdownpad.com/)
- [markPad下载](http://code52.org/DownmarkerWPF/)
- [mdcharm](http://www.mdcharm.com/)
- [在线markdown编辑器](http://dillinger.io/)
- [在线markdown编辑器](http://markable.in/editor/)

## 例子

# Dillinger

    Dillinger is a cloud-enabled, mobile-ready, offline-storage, AngularJS powered HTML5 Markdown editor.

      - Type some Markdown on the left
      - See HTML in the right
      - Magic

    Markdown is a lightweight markup language based on the formatting conventions that people naturally use in email.  As [John Gruber] writes on the [Markdown site] [1]:

    > The overriding design goal for Markdown's
    > formatting syntax is to make it as readable
    > as possible. The idea is that a
    > Markdown-formatted document should be
    > publishable as-is, as plain text, without
    > looking like it's been marked up with tags
    > or formatting instructions.

    This text you see here is *actually* written in Markdown! To get a feel for Markdown's syntax, type some text into the left window and watch the results in the right.

    ### Version
    3.0.2

    ### Tech

    Dillinger uses a number of open source projects to work properly:

    * [AngularJS] - HTML enhanced for web apps!
    * [Ace Editor] - awesome web-based text editor
    * [Marked] - a super fast port of Markdown to JavaScript
    * [Twitter Bootstrap] - great UI boilerplate for modern web apps
    * [node.js] - evented I/O for the backend
    * [Express] - fast node.js network app framework [@tjholowaychuk]
    * [Gulp] - the streaming build system
    * [keymaster.js] - awesome keyboard handler lib by [@thomasfuchs]
    * [jQuery] - duh

    ### Installation

    You need Gulp installed globally:

    ```sh
    $ npm i -g gulp
    ```

    ```sh
    $ git clone [git-repo-url] dillinger
    $ cd dillinger
    $ npm i -d
    $ mkdir -p public/files/{md,html,pdf}
    $ gulp build --prod
    $ NODE_ENV=production node app
    ```

    ### Plugins

    Dillinger is currently extended with the following plugins

    * Dropbox
    * Github
    * Google Drive
    * OneDrive

    Readmes, how to use them in your own application can be found here:

    * plugins/dropbox/README.md
    * plugins/github/README.md
    * plugins/googledrive/README.md
    * plugins/onedrive/README.md

    ### Development

    Want to contribute? Great!

    Dillinger uses Gulp + Webpack for fast developing.
    Make a change in your file and instantanously see your updates!

    Open your favorite Terminal and run these commands.

    First Tab:
    ```sh
    $ node app
    ```

    Second Tab:
    ```sh
    $ gulp watch
    ```

    (optional) Third:
    ```sh
    $ karma start
    ```

    ### Todo's

     - Write Tests
     - Rethink Github Save
     - Add Code Comments
     - Add Night Mode

    License
    ----

    MIT


    **Free Software, Hell Yeah!**

    [john gruber]:http://daringfireball.net/
    [@thomasfuchs]:http://twitter.com/thomasfuchs
    [1]:http://daringfireball.net/projects/markdown/
    [marked]:https://github.com/chjj/marked
    [Ace Editor]:http://ace.ajax.org
    [node.js]:http://nodejs.org
    [Twitter Bootstrap]:http://twitter.github.com/bootstrap/
    [keymaster.js]:https://github.com/madrobby/keymaster
    [jQuery]:http://jquery.com
    [@tjholowaychuk]:http://twitter.com/tjholowaychuk
    [express]:http://expressjs.com
    [AngularJS]:http://angularjs.org
    [Gulp]:http://gulpjs.com
    # Dillinger

    Dillinger is a cloud-enabled, mobile-ready, offline-storage, AngularJS powered HTML5 Markdown editor.

      - Type some Markdown on the left
      - See HTML in the right
      - Magic

    Markdown is a lightweight markup language based on the formatting conventions that people naturally use in email.  As [John Gruber] writes on the [Markdown site] [1]:

    > The overriding design goal for Markdown's
    > formatting syntax is to make it as readable
    > as possible. The idea is that a
    > Markdown-formatted document should be
    > publishable as-is, as plain text, without
    > looking like it's been marked up with tags
    > or formatting instructions.

    This text you see here is *actually* written in Markdown! To get a feel for Markdown's syntax, type some text into the left window and watch the results in the right.

    ### Version
    3.0.2

    ### Tech

    Dillinger uses a number of open source projects to work properly:

    * [AngularJS] - HTML enhanced for web apps!
    * [Ace Editor] - awesome web-based text editor
    * [Marked] - a super fast port of Markdown to JavaScript
    * [Twitter Bootstrap] - great UI boilerplate for modern web apps
    * [node.js] - evented I/O for the backend
    * [Express] - fast node.js network app framework [@tjholowaychuk]
    * [Gulp] - the streaming build system
    * [keymaster.js] - awesome keyboard handler lib by [@thomasfuchs]
    * [jQuery] - duh

    ### Installation

    You need Gulp installed globally:

    ```sh
    $ npm i -g gulp
    ```

    ```sh
    $ git clone [git-repo-url] dillinger
    $ cd dillinger
    $ npm i -d
    $ mkdir -p public/files/{md,html,pdf}
    $ gulp build --prod
    $ NODE_ENV=production node app
    ```

    ### Plugins

    Dillinger is currently extended with the following plugins

    * Dropbox
    * Github
    * Google Drive
    * OneDrive

    Readmes, how to use them in your own application can be found here:

    * plugins/dropbox/README.md
    * plugins/github/README.md
    * plugins/googledrive/README.md
    * plugins/onedrive/README.md

    ### Development

    Want to contribute? Great!

    Dillinger uses Gulp + Webpack for fast developing.
    Make a change in your file and instantanously see your updates!

    Open your favorite Terminal and run these commands.

    First Tab:
    ```sh
    $ node app
    ```

    Second Tab:
    ```sh
    $ gulp watch
    ```

    (optional) Third:
    ```sh
    $ karma start
    ```

    ### Todo's

     - Write Tests
     - Rethink Github Save
     - Add Code Comments
     - Add Night Mode

    License
    ----

    MIT


    **Free Software, Hell Yeah!**

    [john gruber]:http://daringfireball.net/
    [@thomasfuchs]:http://twitter.com/thomasfuchs
    [1]:http://daringfireball.net/projects/markdown/
    [marked]:https://github.com/chjj/marked
    [Ace Editor]:http://ace.ajax.org
    [node.js]:http://nodejs.org
    [Twitter Bootstrap]:http://twitter.github.com/bootstrap/
    [keymaster.js]:https://github.com/madrobby/keymaster
    [jQuery]:http://jquery.com
    [@tjholowaychuk]:http://twitter.com/tjholowaychuk
    [express]:http://expressjs.com
    [AngularJS]:http://angularjs.org
    [Gulp]:http://gulpjs.com
    # Dillinger

    Dillinger is a cloud-enabled, mobile-ready, offline-storage, AngularJS powered HTML5 Markdown editor.

      - Type some Markdown on the left
      - See HTML in the right
      - Magic

    Markdown is a lightweight markup language based on the formatting conventions that people naturally use in email.  As [John Gruber] writes on the [Markdown site] [1]:

    > The overriding design goal for Markdown's
    > formatting syntax is to make it as readable
    > as possible. The idea is that a
    > Markdown-formatted document should be
    > publishable as-is, as plain text, without
    > looking like it's been marked up with tags
    > or formatting instructions.

    This text you see here is *actually* written in Markdown! To get a feel for Markdown's syntax, type some text into the left window and watch the results in the right.

    ### Version
    3.0.2

    ### Tech

    Dillinger uses a number of open source projects to work properly:

    * [AngularJS] - HTML enhanced for web apps!
    * [Ace Editor] - awesome web-based text editor
    * [Marked] - a super fast port of Markdown to JavaScript
    * [Twitter Bootstrap] - great UI boilerplate for modern web apps
    * [node.js] - evented I/O for the backend
    * [Express] - fast node.js network app framework [@tjholowaychuk]
    * [Gulp] - the streaming build system
    * [keymaster.js] - awesome keyboard handler lib by [@thomasfuchs]
    * [jQuery] - duh

    ### Installation

    You need Gulp installed globally:

    ```sh
    $ npm i -g gulp
    ```

    ```sh
    $ git clone [git-repo-url] dillinger
    $ cd dillinger
    $ npm i -d
    $ mkdir -p public/files/{md,html,pdf}
    $ gulp build --prod
    $ NODE_ENV=production node app
    ```

    ### Plugins

    Dillinger is currently extended with the following plugins

    * Dropbox
    * Github
    * Google Drive
    * OneDrive

    Readmes, how to use them in your own application can be found here:

    * plugins/dropbox/README.md
    * plugins/github/README.md
    * plugins/googledrive/README.md
    * plugins/onedrive/README.md

    ### Development

    Want to contribute? Great!

    Dillinger uses Gulp + Webpack for fast developing.
    Make a change in your file and instantanously see your updates!

    Open your favorite Terminal and run these commands.

    First Tab:
    ```sh
    $ node app
    ```

    Second Tab:
    ```sh
    $ gulp watch
    ```

    (optional) Third:
    ```sh
    $ karma start
    ```

    ### Todo's

     - Write Tests
     - Rethink Github Save
     - Add Code Comments
     - Add Night Mode

    License
    ----

    MIT


    **Free Software, Hell Yeah!**

    [john gruber]:http://daringfireball.net/
    [@thomasfuchs]:http://twitter.com/thomasfuchs
    [1]:http://daringfireball.net/projects/markdown/
    [marked]:https://github.com/chjj/marked
    [Ace Editor]:http://ace.ajax.org
    [node.js]:http://nodejs.org
    [Twitter Bootstrap]:http://twitter.github.com/bootstrap/
    [keymaster.js]:https://github.com/madrobby/keymaster
    [jQuery]:http://jquery.com
    [@tjholowaychuk]:http://twitter.com/tjholowaychuk
    [express]:http://expressjs.com
    [AngularJS]:http://angularjs.org
    [Gulp]:http://gulpjs.com

