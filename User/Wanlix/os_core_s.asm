    IMPORT guiNextTaskSp
    IMPORT gpuiCurTaskSpAddr
    
    EXPORT WLX_SwitchToTask
    EXPORT WLX_ContextSwitch
 

    PRESERVE8
	THUMB
		
	AREA CODE, CODE, READONLY

WLX_SwitchToTask

    MOV R2,R0                   ;由于R0是任务的入口函数，因此先将寄存器组地址存入R2寄存器，这样R0就可以被修改
    LDMIA R2!,{R0,R4-R12}       ;把参数中的R0、R4-R12复制到CPU的寄存器中
    LDMIA R2,{R13}              ;把SP复制到CPU的SP寄存器中
    ADD R2 ,#8                  ;R2指向寄存器组中的XPSR
    LDMIA R2,{R1}               ;把XPSR的值读取到CPU的R1中
    MSR XPSR,R1                 ;把R1中刚存入的XPSR值写入到XPSR寄存器
    SUB R2,#4                   ;R2指向寄存器组中的LR
    LDMIA R2,{PC}               ;运行任务

WLX_ContextSwitch

    ;保存当前任务的栈信息
    MOV R3,R0                   ;将寄存器组地址存入R3寄存器
    STMIA R3!,{R0,R4-R12}       ;保存R0、R4~R12寄存器
    STMIA R3!,{R13}             ;保存SP寄存器
    STMIA R3!,{R14}             ;保存LR寄存器
    MRS R2,XPSR                 ;获取XPSR寄存器数值
    STMIA R3,{R2}               ;保存到寄存器组中的XPSR

    ;加载即将要运行任务的栈信息
    LDMIA R1!,{R0,R4-R12}       ;恢复R0、R4~R12寄存器
    LDMIA R1,{R13}              ;恢复SP寄存器
    ADD R1,#8                   ;R1指向寄存器组中的XPSR
    LDMIA R1,{R2}               ;获取寄存器组中的XPSR数值
    MSR XPSR,R2                 ;恢复XPSR寄存器
    SUB R1,#4                   ;R1指向寄存器组中的LR
    LDMIA R1,{PC}               ;切换任务



    
;Old Version 3.2

;WLX_SwitchToTask

    ;R0为入口参数
    ;LDMIA R0!,{R4-R12}          ;把参数中的R4-R12复制到CPU的寄存器中
    ;LDMIA R0,{R13}              ;把SP复制到CPU的SP寄存器中
    ;ADD R0,#8                   ;R0指向XPSR
    ;LDMIA R0,{R1}               ;把XPSR的值读取到CPU的R1中
    ;MSR XPSR,R1                 ;把R1中刚存入的XPSR值写入到XPSR寄存器
    ;SUB R0,#4                   ;R0指向LR
    ;LDMIA R0,{PC}               ;运行任务

;WLX_ContextSwitch

    ;保存当前任务的栈信息，R0是当前任务的StackReg
    ;STMIA R0!,{R4-R12}          ;把当前CPU的R4-R12保存到当前任务的任务栈中
    ;STMIA R0!,{R13}             ;把当前CPU的SP寄存器的值保存到当前任务栈的SP中
    ;STMIA R0!,{R14}             ;把当前CPU的LR寄存器的值保存到当前任务栈的LR中 
    ;MRS R2,XPSR                 ;把当前CPU的XPSR寄存器的值先保存到R2中
    ;STMIA R0,{R2}               ;把刚保存的XPSR值存到当前任务栈的XPSR寄存器中

    ;LDMIA R1!,{R4-R12}          ;代码功能如上述的WLX_SwitchToTask，区别在于入口参数由R0变成了R1
    ;LDMIA R1,R13
    ;ADD R1,#8
    ;LDMIA R1,{R0}
    ;MSR XPSR,R0
    ;SUB R1,#4
    ;LDMIA R1,{PC}

    END
