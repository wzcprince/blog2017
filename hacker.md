

Node.js 独立日漏洞攻击原理_AlibabaInfrastructure_新浪博客
<http://blog.sina.com.cn/s/blog_e59371cc0102vocn.html>

【华安解密之DDoS攻防汇总贴】完美收官，感谢大家的支持，后续电子合集即将亮相，敬请期待！-安全-华为企业互动社区
<http://forum.huawei.com/enterprise/zh/thread-360365.html>

在调试器中看阿里的软件兵团
<http://m.csdn.net/article/2014-09-16/2821705?from=timeline&isappinstalled=0>
- 选择Page faults来衡量软件对功耗的影响
- 以管理员身份运行WinDBG，赐予其系统级的督察权利，然后将其附加到AlipaySecSvc进程
- 对wtsapi32!WTSEnumerateSessionsW设置断点，果然反复命中，还不止一个线程命中断点，居然有多个线程在调用这个沉重的API和触发异常。
- 在kernel32.dll模块下，Process32­NextW赫然在列。这告诉我们，AlipaySecSvc除了调用沉重的WTSEnumerate­Sessions API外，还调用了另一个沉重的API Process32­Next。前者枚举系统中的所有登录会话，而后者枚举会话中的进程。