//
//  ViewController.m
//  msgsend
//
//  Created by 刘泊 on 2019/3/8.
//  Copyright © 2019 LB. All rights reserved.
//

#import "ViewController.h"

#import "Person.h"

#import <objc/message.h>

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    id obj = objc_msgSend(Person.class, @selector(new));
    Class tmp = Person.class;
    Person* tmp2 = [Person new];
    objc_msgSend(tmp2, @selector(setName:),@"张三");
    objc_msgSend(tmp2, @selector(setAge:),100);
    objc_loadWeak(&tmp2);
    //NSLog(@"%@ %d %d",[obj class],[obj isKindOfClass:Person.class],[tmp.self isMemberOfClass:[NSObject class]]);
    NSLog(@"%@ %d %@",tmp2.name,tmp2.age,objc_loadWeak(&tmp2));
}


@end
