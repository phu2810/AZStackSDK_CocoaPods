//
//  StackManager.h
//  AzStack
//
//  Created by Phu Nguyen on 6/21/15.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define AZSERVER_PRODUCTION 1
#define AZSERVER_TEST 2

@class AzStackUser;
@class AzChatRoom;

typedef void (^ConnectWithCompletion)(NSString * authenticatedAzStackUserID, NSError * error, BOOL successful);
typedef void (^GetBlockUserInfoWithComplete)(NSString * azStackUserId, int blockType, NSError * error);
typedef void (^BlockUnblockUserWithComplete)(NSString * azStackUserId, int result, NSError * error);
typedef void (^GetListBlockUserWithComplete)(NSArray * listAzUserIdsBlocked, NSError * error);

@protocol AzUserInfoDelegate <NSObject>
@required
- (void) azRequestUserInfo: (NSArray *) azStackUserIds withTarget: (int) target;
@optional
- (NSArray *) azRequestFriendList;
- (UIViewController *) azRequestUserInfoController: (AzStackUser *) user withAzStackUserId: (NSString *) azStackUserId;
- (void) azFinishGetUserInfo: (NSString *) azStackUserId withUser: (AzStackUser *) user;
- (void) azFinishLoadRecentUsers: (NSArray *) arrays;
@end

@protocol AzChatDelegate <NSObject>
@required
- (UINavigationController *) azRequestNavigationToPushChatController;
@optional
- (void) azUpdateUnreadMessageCount: (int) unreadCount;
- (UIViewController *) azRequestSelectUsersController: (UIViewController *) chatController;
- (void) azRequestShowChatViewController: (UIViewController *) chatController;
- (void) azCustomChatNavigationBar: (UIViewController *) chatController;
- (void) azDidSelectChatRoom: (AzChatRoom *) chatRoom;
@end

@protocol AzCallDelegate <NSObject>
@optional
- (void) azJustFinishCall: (NSDictionary *) callInfo;
@end

@interface AzStackManager : NSObject

+ (AzStackManager*)instance;

@property (nonatomic, weak) id<AzUserInfoDelegate> azUserInfoDelegate;

@property (nonatomic, weak) id<AzChatDelegate> azChatDelegate;

@property (nonatomic, weak) id<AzCallDelegate> azCallDelegate;

- (void) setAppId: (NSString *) appId;

- (void) setPublicKey: (NSString *) publicKey;

- (void) connectWithAzStackUserId: (NSString *) azStackUserID userCredentials: (NSString *) userCredentials fullname: (NSString *)fullname completion: (ConnectWithCompletion)blockProcessResult;

- (void) updateFullnameForPushNotification: (NSString *) name;

- (void) updateUserInfo: (NSDictionary *) userInfo;

- (void) setTintColorNavigationBar: (UIColor *) tintColorNav;

- (void) setLanguage: (NSString *) language;

- (void) setDebugLog: (BOOL) logEnable;

- (void) setHiddenButtonCallInChatNavigationBar: (BOOL) hidden;

- (void) initial;

- (void) settingMessageNotification:(NSDictionary *) dicSetting;

- (NSDictionary *) getCurrentMessageNotificationSetting;

- (UIViewController *) chatWithUser: (NSString *) azStackUserId withUserInfo: (NSDictionary *) userInfo;

- (UIViewController *) chatWithUser: (NSString *) azStackUserId;

- (UIViewController *) createChatGroup;

- (UIViewController *) createChat11;

- (void) sendUserInfoToAzStack:(NSArray *) userInfos withTarget: (int) target;

- (UIViewController *) chatWithGroup: (NSArray *) azStackUserIds withGroupInfo: (NSDictionary *) groupInfo;

- (UIViewController *) getChattingHistory;

- (void) callWithUser: (NSString *) azStackUserId withUserInfo: (NSDictionary *) userinfo;

- (void) callWithUser: (NSString *)azStackUserId;

- (void) callVideoWithUser: (NSString *) azStackUserId withUserInfo: (NSDictionary *) userinfo;

- (void) callVideoWithUser: (NSString *)azStackUserId;

- (void) doneSelectUsers: (UIViewController *) chatController withListAzStackUsers: (NSArray *) listAzStackUsers;

- (void) registerForRemoteNotificationsWithDeviceToken: (NSData *) deviceToken;
- (void) processLocalNotify: (UILocalNotification *)notif;
- (void) processRemoteNotify:(NSDictionary *)userInfo;
- (void) unregisterPushNotification;
//
- (void) disconnectAzServer;
- (void) clearAllAzData;
- (void) disconnectAndClearAllData;
//
- (void) getBlockUserInfo: (NSString *) azStackUserId withCompleteHandler: (GetBlockUserInfoWithComplete) handler;
//
- (void) changeBlockInfoForUser: (NSString *) azStackUserId withBlockInfo: (int) blockInfo withCompleteHandler: (BlockUnblockUserWithComplete) handler;
//
- (void) getListBlockUserWithCompleteHandler: (GetListBlockUserWithComplete) handler;
//
- (UIViewController*) getChatRooms;
//
- (UIViewController*) getChannelListController;
//

- (AzStackUser *) getAzUser: (NSString *) azStackUserId;

- (NSArray *) getRecentAzUsersList;

@end
