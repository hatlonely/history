tools
=====

We have a lot of similar job, and a good practise is turn our job to a shell tool so that we can finish our job
efficiently. So I have some tools. But every time I want to use those tools, I must download them first. and I should
update for everytime it changes. It's a big cost for maintenance if we have a lot of machines. So I'm thinking whether we
can jun run the code remotely without download. And here is the soluation.

install
-------

You can easily install by the follow command:

```
alias hsh='sh -c "$(curl -s https://raw.githubusercontent.com/hatlonely/tools/master/hsh)" -c'
```

or append the line to your `.bash_profile` or `.zshrc`


usage
-----

```
hsh <command>
```
