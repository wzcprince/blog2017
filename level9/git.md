

#技巧列表

## checkout-orphan-大幅提高下载速度

<font size = "10">NO PULL REQUESTS PLEASE</font>

Git is not a fan of what we're doing here. To combat this, we use git checkout --orphan, which very effectively discards all the history of the branch for each tarball. **The benefit is much shorter download times, since there's no big binary history**.

参见 <https://github.com/tianon/docker-brew-ubuntu-core/tree/a2573609340194bf33712c1fa2dc4de8f9b70ca2#tldr-no-pull-requests-please>

参见 git checkout 命令详解 - 胡涛儿 - 博客园
<http://www.cnblogs.com/hutaoer/archive/2013/05/07/git_checkout.html>
4. git checkout --orphan <branch>

是的，假如你的某个分支上，积累了无数次的提交，你也懒得去打理，打印出的log也让你无力吐槽，那么这个命令将是你的神器，它会基于当前所在分支新建一个赤裸裸的分支，没有任何的提交历史，但是当前分支的内容一一俱全。新建的分支，严格意义上说，还不是一个分支，因为HEAD指向的引用中没有commit值，只有在进行一次提交后，它才算得上真正的分支。还等什么呢？赶紧试试！

#帖子列表
Git Community Book 中文版 http://gitbook.liuhui998.com/index.html

rebase http://gitbook.liuhui998.com/4_2.html

## 5月10日王强git
 
工作区working
暂存区cached
repo
还有远端库
head指针？指向当前的工作分支
 
revert和reset
推到远端之后，必须用revert并且生成commit点以及日志，
用reset非常危险！别人再push的时候会把去掉的点又搞回来！
 
commit之后，那个点即使在log里看不到，也能找回来
 
reset之后，那些点并不会被删掉，别人再fetch
 
 
git commit --amend把修改合并到最后一个commit点
如果已经推到远端库就不能用了！！
 
 
发出去的mr会把随后的修改也会夹带到子系统中！所以一个问题单要拉一个分支来改，发出mr之后，自己远端库里的分支就不能再变了！！！

## Git工作流指南 Pull Request工作流
http://blog.jobbole.com/76854/
解析Pull Request

当要发起一个Pull Request，你所要做的就是请求（Request）另一个开发者（比如项目的维护者），来pull你仓库中一个分支到他的仓库中。这意味着你要提供4个信息（源仓库、源分支、目的仓库、目的分支），以发起Pull Request。



