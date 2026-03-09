_This project has been created as part of the 42 curriculum by nofelten and acohaut._

# Minishell

_nofelten & acohaut_  
_(piscine of september's 2025 - 42 PARIS)_  


<ins>starting date</ins> : 26/01/2026  
<ins>last update</ins> : 07/03/2026  


## Description  
The shell is a command language interpreter.  
Minishell is a project that teaches us (after Pipex) processes (parent and child), how to execute a command as a shell, redirect streams, parse inputs (similar as bash) etc..  

We need to mimic the bash :  
***lexer*** (tokenizer) > ***parser*** (syntax) > ***expander*** (env var) > ***redirection*** (pipe/fd) > ***executor***

We need to handle signals (CTRL-C, CTRL-D, CTRL-\\) and built-in functions as well :  
- echo (with flag -n)
- cd
- env
- exit
- unset
- export
- pwd


## Instructions  
***Usage***  
1) make all
2) ./minishell (no args)
3) execute commands in our minishell

***Examples***  
*in minishell :*
```bash
> ls -la | grep "." | wc
> < Makefile wc | cat > out
> << EOF cat
> echo "hi $USER, you're currently here : $PWD"
> export NEWVAR=blabla (then again export to see the result)
> unset NEWVAR
> cd srcs/
> echo -n hello >> out
> echo $?
> env
> pwd
```  

***Check leaks***  
valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all ./minishell


## Ressources  
<ins>Bash features</ins> :   
(https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)  
(https://www.gnu.org/software/bash/manual/bash.html)  
<ins>Fork()</ins> : (https://www.youtube.com/watch?v=PwxTbksJ2fo)  
<ins>Open()</ins> : (https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/)  
<ins>Signals</ins> : (https://www.geeksforgeeks.org/c/signals-c-language/)  
<ins>Built-in functions</ins> : man pages (#RTFM)  
<ins>Other ressources</ins> : Github and IA -> for researches and understanding concepts or examples usages for functions allowed by the subject  
